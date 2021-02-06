#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

// �ַ�� ����
#define ����˻�
// �ַ�� ����
//*
#ifdef ���ڿ�����
// �ڵ��ۼ���: ExtremeCode
// ��ũ: https://programmers.co.kr/learn/courses/30/lessons/60057
// ����: ���ڿ� ���� string compression
// Ǯ�̼���: ���ڿ��� ����(���ݺ���~3����)�Ͽ� ���������� ã��, ������ ����� �����Ͽ� �����Ѵ�.
// ����: Ȥ�� ���ڿ��� �̷� ������� �����ϴ� ����������? 7zip�� text������ � ������� �����ϴ��� ã�ƺ��߰ڴ�.
int solution( string s ) {
	size_t s_lenght = s.length();
	if ( s_lenght < 3 )
		return s_lenght;

	int answer = s_lenght;
	int iSplitSize = s_lenght / 2;
	int iSplitCount = 0;
	do
	{
		vector<string> vecStrSplit;
		iSplitCount = s_lenght / iSplitSize;
		for ( size_t i = 0; i < s_lenght; i += iSplitSize )
		{
			string strSplit = s.substr( i, iSplitSize );

			vecStrSplit.push_back( strSplit );
		}

		string strResult;
		int iCompareCount = 1;
		string strCompareStr = vecStrSplit[0];
		for ( size_t i = 1; i < vecStrSplit.size(); ++i )
		{
			//���ڿ��� ���ٸ� ī��Ʈ ����, �ٸ��ٸ� ��� ��� ����.
			if ( !strCompareStr.compare( vecStrSplit[i] ) )
			{
				++iCompareCount;
			}
			else
			{
				if ( iCompareCount > 1 ) {
					strResult.append( to_string( iCompareCount ) );
				}
				iCompareCount = 1;
				strResult.append( strCompareStr );

				strCompareStr = vecStrSplit[i];
			}
		}
		{
			if ( iCompareCount > 1 ) {
				strResult.append( to_string( iCompareCount ) );
			}
			strResult.append( vecStrSplit[vecStrSplit.size() - 1] );
		}
		cout << strResult << endl;

		answer = answer < strResult.size() ? answer : strResult.size();

	} while ( --iSplitSize && iSplitSize > 0 );

	return answer;
}
#endif //���ڿ�����
//*/

//*
#ifdef ��ȣ��ȯ
// �ڵ��ۼ���: ExtremeCode
// ��ũ: https://programmers.co.kr/learn/courses/30/lessons/60058
// ����: ��ȣ ��ȯ parenthesis conversion
// Ǯ�̼���: ��ȣ�� ¦�� ���ߴ� �˰���, ����Ǯ�̿� ���ִ� ��ƾ�� ���� ���� �ڵ�. 

//�������� ��ȣ ���ڿ�
bool isBalancedParenthesisString( string _str )
{
	int iCheck = 0;
	for ( const auto& i : _str )
	{
		if ( i == '(' ) ++iCheck;
		else --iCheck;
	}

	if ( iCheck == 0 )
		return true;

	return false;
}

int splitting_ParenthesisString_Return_CorrectStringIndex( string _str )
{
	int iCheck = 0;
	for ( size_t i = 0; i < _str.length(); ++i )
	{
		if ( _str[i] == '(' ) ++iCheck;
		else --iCheck;

		if ( iCheck == 0 ) return i + 1;
	}

	return 0;
}

//�ùٸ� ��ȣ ���ڿ�
bool isCorrectParenthesisString( string _str )
{
	int iCount = 0;
	for ( size_t i = 0; i < _str.length(); ++i )
	{
		if ( _str[i] == '(' ) ++iCount;
		else --iCount;

		if ( iCount < 0 ) return false;
	}
	return true;
}
string solution( string p )
{
	size_t iStrLength = p.length();
	//�� ���ڿ��� ���, ���� ��ȣ ���ڿ��� ��� ��ȯ.
	if ( iStrLength == 0 || isCorrectParenthesisString( p ) )
		return p;

	string answer = "";

	int iSplitIndex = splitting_ParenthesisString_Return_CorrectStringIndex( p );

	string u = p.substr( 0, iSplitIndex );
	string v = p.substr( iSplitIndex );

	if ( isCorrectParenthesisString( u ) )
		answer = u + solution( v );
	else
	{
		answer.append( "(" );
		answer.append( solution( v ) );
		answer.append( ")" );

		for ( size_t i = 1; i < u.length() - 1; ++i )
		{
			if ( u[i] == '(' ) answer.append( ")" );
			else answer.append( "(" );
		}
	}

	return answer;
}

#endif //��ȣ��ȯ
//*/

//*
#ifdef �ڹ���Ϳ���
// �ۼ���: ExtremeCode
// ��ũ: https://programmers.co.kr/learn/courses/30/lessons/60059
// ����: �ڹ���� ���� Lock and key
// Ǯ�̼���: ������ �������� �ٲ㼭 Ǯ��Ҵ�. Lock�� �������� Ű�� ���� ��ư��鼭 ���ߴ� ����� �ƴ�, Lock�� �ּ����� ������ ���ϰ� key�� �������� Lock�� ���� ���纸�� ������� Ǯ����.

//key�� �������� ��ġ�ϴ� ������ �߽߰� Ž���� �����Ѵ�.
bool isOpen( const vector<vector<int>>& key, const vector<vector<int>>& spaceToLock )
{
	int ikeyYSize = static_cast<int>(key.size());
	int iKeyXSize = static_cast<int>(key[0].size());
	int iSpaceToLockYSize = static_cast<int>(spaceToLock.size());
	int iSpaceToLockXSize = static_cast<int>(spaceToLock[0].size());

	// key�� spaceToLock���� �۴ٸ� ���߾� �� �ʿ䵵 ���� false�̴�.
	if ( ikeyYSize < iSpaceToLockYSize || iKeyXSize < iSpaceToLockXSize )
		return false;

	int iCount = 0;
	int iMaxCount = iSpaceToLockXSize * iSpaceToLockYSize;

	for ( int row = 0; row <= ikeyYSize - iSpaceToLockYSize; ++row )
	{
		for ( int col = 0; col <= iKeyXSize - iSpaceToLockXSize; ++col )
		{
			// ��ġ-> Ž�� ����.
			if ( spaceToLock[0][0] == key[row][col] )
			{
				bool bBreak = false;
				iCount = 0;
				for ( int i = 0; i < iSpaceToLockYSize; ++i )
				{
					for ( int j = 0; j < iSpaceToLockXSize; ++j )
					{
						if ( spaceToLock[i][j] == key[row + i][col + j] )
							++iCount;
						else
						{
							bBreak = true;
							iCount = 0;
							break;
						}
					}
					if ( bBreak )
						break;
				}

				if ( iCount == iMaxCount )
					return true;
			}
		}
	}

	return false;
}

// SpaceToLock�� ���迭�� �ƴϱ� ������ �� ȸ�� ����� ä���ߴ�.
vector<vector<int>> Rotation_2DVector_Right( const vector<vector<int>>& SpaceToLock )
{
	int iYSize = static_cast<int>(SpaceToLock.size());
	int iXSize = static_cast<int>(SpaceToLock[0].size());
	vector<vector<int>> vecResult;

	for ( int i = 0; i < iXSize; ++i )
	{
		vector<int> vecNewRow;
		for ( int j = iYSize - 1; j >= 0; --j )
		{
			vecNewRow.push_back( SpaceToLock[j][i] );
		}
		vecResult.push_back( vecNewRow );
	}

	return vecResult;
}

// Lock�� �� ������ ã�� ���ο� 2d vector�� ����� ����Ѵ�. �� ����� ����� �� padding�� shift���� key�� ���߾� �� �� �ִ� ����̴�.
vector<vector<int>> SpaceToLock( const vector<vector<int>>& lock )
{
	vector<vector<int>> vecSpaceToLock;
	vector<pair<int, int>> vecSpaceTmp;
	// �����ѹ�
	int iX_Start = 999, iX_End = -1;
	int iY_Start = 999, iY_End = -1;
	for ( int row = 0; row < static_cast<int>(lock.size()); ++row )
	{
		for ( int col = 0; col < static_cast<int>(lock.size()); ++col )
		{
			if ( lock[row][col] == 0 )
			{
				iX_Start = iX_Start < col ? iX_Start : col;
				iX_End = iX_End < col ? col : iX_End;

				iY_Start = iY_Start < row ? iY_Start : row;
				iY_End = iY_End < row ? row : iY_End;

				vecSpaceTmp.push_back( make_pair( row, col ) );
			}
		}
	}

	if ( iX_Start != 999 && iX_End != -1 && iY_Start != 999 && iY_End != -1 )
	{
		vecSpaceToLock.assign( iY_End + 1 - iY_Start, vector<int>( iX_End + 1 - iX_Start, 0 ) );

		for ( const auto& i : vecSpaceTmp )
		{
			vecSpaceToLock[i.first - iY_Start][i.second - iX_Start] = 1;
		}
	}

	return vecSpaceToLock;
}

bool solution( vector<vector<int>> key, vector<vector<int>> lock ) {
	bool answer = false;
	vector<vector<int>> vecSpaceToLock;
	vecSpaceToLock = SpaceToLock( lock ); // move

	if ( vecSpaceToLock.empty() )
		return true;

	answer = isOpen( key, vecSpaceToLock );
	if ( answer )
		return answer;

	//3�� ȸ��
	for ( int i = 0; i < 3; ++i ) {
		vecSpaceToLock = Rotation_2DVector_Right( vecSpaceToLock ); // move
		answer = isOpen( key, vecSpaceToLock );
		if ( answer )
			return answer;
	}

	return answer;
}
#endif //�ڹ���Ϳ���
//*/

//*
#ifdef ����˻�
// �ۼ���: ExtremeCode
// ��ũ: https://programmers.co.kr/learn/courses/30/lessons/60060
// ����: ���� �˻� lyrics Search
// Ǯ�̼���: 
// ����: 
#include <regex>
#include <algorithm>

bool compString( const string& _str1, const string& _str2 )
{
	bool _bAscending = true;
	if ( _str1.length() != _str2.length() ) {
		if ( _bAscending )
			return _str1.length() < _str2.length();
		else
			return _str1.length() > _str2.length();
	}
	else
	{
		if ( _bAscending )
			return _str1 < _str2;
		else
			return _str1 > _str2;
	}
}

void replaceAll( std::string& str, const std::string& from, const std::string& to ) {
	if ( from.empty() )
		return;
	size_t start_pos = 0;
	while ( (start_pos = str.find( from, start_pos )) != std::string::npos ) {
		str.replace( start_pos, from.length(), to );
		start_pos += to.length();
	}
}

vector<int> solution( vector<string> words, vector<string> queries ) {
	vector<int> answer;

	std::sort( words.begin(), words.end(), compString );

	for ( auto& str_q : queries )
	{
		int iCount = 0;
		string str_lower = str_q;
		string str_upper = str_q;
		int iLower, iUpper;

		replaceAll( str_q, "?", "." );
		replaceAll( str_lower, "?", "a" );
		replaceAll( str_upper, "?", "z" );

		iLower = lower_bound( words.begin(), words.end(), str_lower, compString ) - words.begin();
		iUpper = upper_bound( words.begin(), words.end(), str_upper, compString ) - words.begin();

		//str_q = std::regex_replace( str_q, std::regex("[?]"), "." ); // ���� �ɷȴ�.

		regex re( str_q );

		for ( size_t i = iLower; i < iUpper; ++i )
		{
			bool bSearch = std::regex_match( words[i], re );

			if ( bSearch )
				++iCount;
		}

		answer.push_back( iCount );
	}

	return answer;
}

template<typename T>
std::ostream &operator <<( std::ostream &os, const std::vector<T> &v ) {
	std::copy( v.begin(), v.end(), std::ostream_iterator<T>( os, ", " ) );
	return os;
}
#endif //����˻�
//*/

//*/
#ifdef �Ҽ��Ǻ�
bool isPrimeNumber( uint64_t _num )
{
	// ���ڸ� ���� ã�´�.
	uint64_t iLastNum = _num % 10;

	if ( iLastNum == 1 || iLastNum == 3 || iLastNum == 7 || iLastNum == 9 )
	{
		return true; // ������
	}
	else if ( _num < 7 )
	{
		if ( iLastNum == 2 || iLastNum == 5 )
			return true;
	}
	else
		return false;

	// 7�ʰ��� ���� �� �ڸ��� 1,3,7,9 �� �Ҽ��� �� �� �ִ�. 1��üũ
}
#include <iomanip>
#include <set>
void EXC_Stlye( const set<uint64_t>& _vecPrime )
{
	uint64_t num = 10;
	vector<int> vecLastNum = { 1, 3, 7, 9 };
	string str;

	bool bFlag = true;
	bool bPrevFlag = bFlag;

	uint64_t iCount = 0;
	vector<uint64_t> vecCount;

	while ( num <= *(--_vecPrime.end()) )
	{
		for ( size_t i = 0; i < 4; ++i )
		{
			uint64_t newNum = num + vecLastNum[i];

			set<uint64_t>::iterator iter = _vecPrime.find( newNum );
			if ( iter != _vecPrime.end() ) // ���� 
			{
				str.append( "1" );

				bFlag = true;
			}
			else //����
			{
				str.append( "0" );

				bFlag = false;
			}
		
			++iCount;

			if ( bFlag != bPrevFlag )
			{
				--iCount;
				vecCount.push_back( iCount );
				iCount = 1;
			}

			bPrevFlag = bFlag;
		}
		num += 10;
	}

	const char *pStr = str.c_str();

	size_t i = 0;
	uint64_t iAddNum = 0;

	vector<pair<uint64_t, uint64_t>> vecPair;
	while ( pStr[i] != 0 )
	{
		size_t iLastNum = i % 4;
		//if ( iLastNum == 0 )
		//{
		//	if ( pStr[i] == '1' )
		//		iAddNum = 2 * 2 * 2;
		//}
		//else if ( iLastNum == 1 )
		//{
		//	if ( pStr[i] == '1' )
		//		iAddNum += 2 * 2;
		//}
		//else if ( iLastNum == 2 )
		//{
		//	if ( pStr[i] == '1' )
		//		iAddNum += 2;
		//}
		//else
		//{
		//	if ( pStr[i] == '1' )
		//		iAddNum += 1;
		//}

		cout << pStr[i];
		++i;


		//if ( i % 4 == 0 )
		//{
		//	cout << std::setw( 6 ) << i / 4 * 10 << std::setw( 6 ) << iAddNum;
		//	vecPair.push_back( make_pair( i / 4 * 10, iAddNum ) );
		//	cout << endl;
		//	iAddNum = 0;
		//}
	}
	cout << "\n"<<str.length() << "���� ����" << endl;

	cout << "2�� ����" << endl;
	for ( const auto& uNum : vecCount )
	{
		cout << uNum;
	}
	cout << "\n���� ����" << "  " << vecCount.size() << "���� ����"<< endl;

	cout << "�� ������ ����" << str.length() - vecCount.size() << "    �� ����� : " << (float)(str.length() - vecCount.size()) / str.length() * 100<< endl;



	/*/
	sort( vecPair.begin(), vecPair.end(), []( const pair<uint64_t, uint64_t>& _number1, const pair<uint64_t, uint64_t>& _number2 )
	{
		if ( _number1.second == _number2.second )
		{
			return _number1.first < _number2.first;
		}

		return _number1.second < _number2.second;
	} );


	for ( const auto& vec : vecPair )
	{
		cout << vec.first << std::setw( 6 ) << vec.second << endl;
	}
	//*/
}

#endif //�Ҽ��Ǻ�
//*/

int main()
{
	//vector<string> words = { "frodo", "front", "frost", "frozen", "frame", "kakao" };
	//vector<string> queries = { "fro??", "????o", "fr???", "fro???", "pro?" };
	//vector<int> result;
	//result = solution( words, queries );

	//cout << result << endl;

	return 0;
}

