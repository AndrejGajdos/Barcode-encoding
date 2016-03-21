#ifndef PB161_HW02_BARCODEEAN13_H
#define PB161_HW02_BARCODEEAN13_H

#include "BarCode.h"

#include <ostream>
#include <string>

class CBarCodeEAN13 : CBarCode {
        int m_digits[12];
        int m_checksum;
        std::string m_encodeString;

public:

    static const std::string ParityEncodings[];
	static const std::string EndBar;
	static const std::string MiddleBar;
	static const std::string LeftOddCoding[];
	static const std::string LeftEvenCoding[];
	static const std::string RightCoding[];

	/**
	 * Constructor of the base class, can be called only from the constructors of inherited classes.
	*/
	CBarCodeEAN13(const int *eanCode);

	/**
	 * Constructor of the base class, can be called only from the constructors of inherited classes.
	*/
	CBarCodeEAN13(const std::string& eanCode);

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
	 * @return constant value on begging m_digits.
	*/
	const int* Digits() const;

	/**
	 * @return current value checksum.
	*/
	int CheckSum() const;

private:

	/**
	 * @return current value checksum counted from stored data.
	*/
	int ComputeCheckSum() const;

	/**
	 * Encodes current values to the barcode.
	*/
	void Encode();

};

#endif // BARCODEEAN13_H_INCLUDED
