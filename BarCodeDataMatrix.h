#ifndef PB161_HW02_BARCODEDATAMATRIX_H
#define PB161_HW02_BARCODEDATAMATRIX_H

#include "BarCode.h"

#include <ostream>
#include <string>

class CBarCodeDataMatrix : public CBarCode{
        bool * * m_data;
        std::size_t m_size;

public:

	/**
	 * Constructor of the base class, can be called only from the constructors of inherited classes.
	*/
	CBarCodeDataMatrix(const std::string& data, std::size_t dataMatrixSize);

	/**
	 * Destructor of the base class, has to be virtual if any of the descendants allocates any resources which need to be taken care of beforehand.
	*/
	~CBarCodeDataMatrix();

	/**
	 * @return current value m_size atribute.
	*/
	std::size_t Size() const;

	/**
	 * Zeroes the content of the barcode.
	*/
	void Zero();

	/**
	 * Outputs the content of the barcode on a console window.
	*/
	void Print() const;

	/**
	 * Depends on the descendant class.
	 *
	 * @return	TRUE if the content of the barcode is valid, FALSE otherwise.
	*/
	bool IsValid() const;

	/**
	 * Parses the input string and fills the barcode with its content.
	 *
	 * @param[in]	data	String to be parsed.
	 * @return		TRUE if the string was successfully parsed(i.e. contained enough data and no unknown characters), FALSE otherwise.
	*/
	bool ParseInput(const std::string& data);

	/**
	 * Exports the content of the barcode to the SVG file. (In our case standard output will do.)
	 *
	 * @param[in]	scale		Determines the scale of the barcode, depending on the context.
	 * @param[in]	offsetX		Sets the distance from the point [0,0] to the left side of the barcode (offset on the X-axis).
	 * @param[in]	offsetY		Sets the distance from the point [0,0] to the top side of the barcode (offset on the Y-axis).
	 * @param[in]	svgHeader	Exports the barcode data alongside with the SVG header and closing element (optional argument).
	 * @return		TRUE if the barcode was exported successfully, FALSE if anything went wrong.
	*/
	void ExportToSVG(std::size_t scale, std::size_t offsetX, std::size_t offsetY, bool svgHeader = false) const;

	/**
	 * Allocate memory
	 *
	 * @return	TRUE if the allocate memory was successfully, FALSE otherwise.
	*/
	bool AllocateMemory();

	/**
	 * Deallocate memory
	*/
    void ReleaseMemory();
};



#endif // BARCODEDATAMATRIX_H_INCLUDED
