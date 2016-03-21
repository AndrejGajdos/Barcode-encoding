#include "BarCodeEAN13.h"

#include <iostream>
#include <string.h>
#include <cctype>

using namespace std;

const string CBarCodeEAN13::ParityEncodings[] = {"111111", "110100", "110010", "110001", "101100", "100110", "100011", "101010", "101001", "100101"};
const string CBarCodeEAN13::EndBar = "101";
const string CBarCodeEAN13::MiddleBar = "01010";
const string CBarCodeEAN13::LeftOddCoding[] = {"0001101", "0011001", "0010011", "0111101", "0100011", "0110001", "0101111", "0111011", "0110111", "0001011"};
const string CBarCodeEAN13::LeftEvenCoding[] = {"0100111", "0110011", "0011011", "0100001", "0011101", "0111001", "0000101", "0010001", "0001001", "0010111"};
const string CBarCodeEAN13::RightCoding[] = {"1110010", "1100110", "1101100", "1000010", "1011100", "1001110", "1010000", "1000100", "1001000", "1110100"};


CBarCodeEAN13::CBarCodeEAN13(const int *eanCode){

	if (eanCode == NULL)
		Zero();
	else {
		for(int i = 0; i<12; i++){
			m_digits[i] = *(eanCode + i);
		}
	}

    m_checksum = ComputeCheckSum();
    Encode();

}

CBarCodeEAN13::CBarCodeEAN13(const std::string& eanCode){
	 ParseInput(eanCode);
	 m_checksum = ComputeCheckSum();
	 Encode();
}

void CBarCodeEAN13::Zero(){

    memset(m_digits, 0, 12*sizeof(int));
    m_checksum = ComputeCheckSum();
    Encode();

}


void CBarCodeEAN13::Print() const{

	for (int i=0; i<12; i++)
		cout << m_digits[i];
	cout << m_checksum;
}


bool CBarCodeEAN13::IsValid() const{

    for(int i=0; i<12; i++) {
        if (m_digits[i] > 9 || m_digits[i] < 0)
            return false;
    }

    if (CheckSum() != ComputeCheckSum())
    	return false;

    return true;

}


bool CBarCodeEAN13::ParseInput(const std::string& data){

	int tempParse = 0;

	Zero();

    for(unsigned int i = 0; i<data.length(); i++) {

         if(isdigit(data[i])) {
    	       m_digits[tempParse] = data[i] - 48;
    	       tempParse++;
    	       if(tempParse >= 12) {
    	          break;
    	       }
    	  } else if(isspace(data[i])) {

    	  } else {
    	       m_checksum = ComputeCheckSum();
    	       return false;
    	        }
    	  }

    	   if(tempParse < 12) {
    	    	m_checksum = ComputeCheckSum();
    	    	return false;
    	    }

    	  m_checksum = ComputeCheckSum();

    	  return true;

}


void CBarCodeEAN13::ExportToSVG(std::size_t scale, std::size_t offsetX, std::size_t offsetY, bool svgHeader) const{

    int width = 0;
    int height = 0;
    int high = 0;
    string color;
    int vyska;
    int temp_ofsetX = offsetX-(8*scale);
    int font = 10*scale;

    width = scale * (3+ 42 + 5 + 42 + 3);
    height = 0.65 * width;
    high = 0.9 * height;

    if (svgHeader){

    		cout << XMLVersion << endl;
			cout << Doctype << endl;
			cout << SVGHeader << endl;
    }

    if(IsValid()) {

    	for (int i = 0; i < 95; i++){

                if (m_encodeString[i] == '1')
                    color = "black";
                if (m_encodeString[i] == '0')
                    color = "white";

                if (i<3 || i > 91 || (i > 45 && i < 50))
                    vyska = height;
                else
                    vyska = high;

                cout << "<rect x=\"" << offsetX << "\" y=\"" << offsetY << "\" width=\"" << scale << "\" height=\"" << vyska << "\" fill=\"" << color << "\" />" << endl;

                offsetX += scale;
            }


            for (int i=0; i<13;i++){

            	if (i == 12)
            	    cout << "<text x=\"" << temp_ofsetX << "\" y=\"" << offsetY+(scale+high+7*scale) << "\" style=\"font-size:" << font << "px\">"<< m_checksum << "</text>" << endl;

                cout << "<text x=\"" << temp_ofsetX << "\" y=\"" << offsetY+(scale+high+7*scale) << "\" style=\"font-size:" << font << "px\">"<< m_digits[i] << "</text>" << endl;

                if(i==0)
                    temp_ofsetX += (6*scale);

                if(i==6)
                	temp_ofsetX += (3*scale);

                	temp_ofsetX += (7*scale);
                }
        }

    if(svgHeader)
            cout << "</svg>";

}

const int* CBarCodeEAN13::Digits() const{

    return m_digits;

}

int CBarCodeEAN13::CheckSum() const{

    return m_checksum;

}

int CBarCodeEAN13::ComputeCheckSum() const{

    int suma = 0;

    for(int i=0; i<12; i++) {
        if (i % 2 == 0)
            suma += 1*m_digits[i];
        else
            suma += 3*m_digits[i];
    }

    return (10 - (suma % 10)) % 10;

}

void CBarCodeEAN13::Encode(){

m_encodeString.erase();

if (IsValid()){

    m_encodeString.append(EndBar);

    string tempParity;
    tempParity.append(ParityEncodings[m_digits[0]]);


    for (int i = 0; i<6; i++){
    if (tempParity[i] == '1')
        m_encodeString.append(LeftOddCoding[m_digits[i+1]]);
    if (tempParity[i] == '0')
        m_encodeString.append(LeftEvenCoding[m_digits[i+1]]);
    }

    m_encodeString.append(MiddleBar);

    for (int i=6;i<11;i++) {
    m_encodeString.append(RightCoding[m_digits[i+1]]);
    }

    m_encodeString.append(RightCoding[m_checksum]);

    m_encodeString.append(EndBar);
    }

}
