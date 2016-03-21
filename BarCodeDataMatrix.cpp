#include "BarCodeDataMatrix.h"

#include <iostream>

using namespace std;


CBarCodeDataMatrix::CBarCodeDataMatrix(const std::string& data, std::size_t dataMatrixSize):m_size(dataMatrixSize){

    m_data = NULL;

    if (dataMatrixSize > 0)
       if (AllocateMemory())
    	   ParseInput(data);

}


CBarCodeDataMatrix::~CBarCodeDataMatrix() {
	if(IsValid())
		ReleaseMemory();
}


void CBarCodeDataMatrix::Zero(){

	if (IsValid()){

		for(unsigned int i = 0; i < m_size; i++) {
			for(unsigned int j = 0; j < m_size; j++) {
		         m_data[i][j] = false;
			}

		}
	}
}


void CBarCodeDataMatrix::Print() const {

	if (IsValid()) {

		for(unsigned i = 0; i < m_size; i++) {
	        	for(unsigned j = 0; j < m_size; j++) {
	        		if(m_data[i][j])
	        			cout << '#';
	        		else
	        			cout << ' ';
	        	}
	        	if(i != m_size-1)
	        		cout << endl;
	    	}
		}
}


bool CBarCodeDataMatrix::IsValid() const{

	 if(m_data == NULL)
	        return false;

	 return true;
}


bool CBarCodeDataMatrix::ParseInput(const std::string& data){

	 if(!IsValid())
	        return false;

    unsigned int tempParse = 0;

    Zero();

    for(unsigned int i = 0 ; i < data.length(); i++){

    	if(data[i] == '0') {

    	            m_data[tempParse/m_size][tempParse%m_size] = 0;
    	            tempParse++;
    	            if(tempParse == m_size*m_size)
    	                break;

    	} else if(data[i] == '1') {

    	            m_data[tempParse/m_size][tempParse%m_size] = 1;
    	            tempParse++;
    	            if(tempParse == m_size*m_size)
    	                break;

    	} else if(isspace(data[i])) {

    	} else
    	    return false;

    	    }

    	if(tempParse < m_size*m_size)
    	   return false;

    	return true;
    	}



void CBarCodeDataMatrix::ExportToSVG(std::size_t scale, std::size_t offsetX, std::size_t offsetY, bool svgHeader) const {

    string color;
    int ofsetX = offsetX;
    int ofsetY = offsetY;

    if (svgHeader){

            cout << XMLVersion << endl;
            cout << Doctype << endl;
            cout << SVGHeader << endl;

    }

    if(IsValid()) {

            for (unsigned int i = 0; i < m_size; i++) {
            	for (unsigned int j = 0; j < m_size; j++){

                if (m_data[i][j] == 1)
                    color = "black";
                if (m_data[i][j] == 0)
                    color = "white";

                cout << "<rect x=\"" << ofsetX << "\" y=\"" << ofsetY << "\" width=\"" << scale << "\" height=\"" << scale << "\" fill=\"" << color << "\" />" << endl;

                if (j / (m_size-1) == 1)
                    ofsetX = offsetX;
                else
                    ofsetX += scale;

                if (j / (m_size-1) == 1)
                    ofsetY += scale;

            	}
            }
        }

    if(svgHeader) {
           cout << "</svg>";
       }

}

std::size_t CBarCodeDataMatrix::Size() const{
    return m_size;
}


bool CBarCodeDataMatrix::AllocateMemory()
{
	this->m_data = new (nothrow) bool * [m_size];

	// Try to allocate an array of pointers
	if(!this->m_data)
		return false;

	for(size_t y = 0; y < m_size; y++)
	{
		// Allocate a new row of the map
		this->m_data[y] = new (nothrow) bool[m_size];

		if(!this->m_data[y])
		{
			// In case anything fails, delete everything that has been allocated up to this point
			cerr << "ERROR: DataMatrix::AllocateMemory() - Not enough memory!" << endl;

			for(size_t i = 0; i < y; i++)
				delete this->m_data[i];

			delete this->m_data;
			this->m_data = NULL;

			return false;
		}
	}

	return true;
}

void CBarCodeDataMatrix::ReleaseMemory()
{
	if(!this->m_data)
		return;

	// Deallocate every row
	for(size_t y = 0; y < this->m_size; y++)
	{
		if(this->m_data[y])
		{
			delete this->m_data[y];
			this->m_data[y] = NULL;
		}
	}

	// Deallocate the array of the pointers
	if(this->m_data)
		delete this->m_data;

	this->m_data = NULL;
}
