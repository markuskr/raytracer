#ifndef GETOPERATOR_H_
#define GETOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"



#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>

class GetOperator  : public GMLOperator 
{
public:
	GetOperator(std::vector<GMLToken> &stack, 
		std::vector<std::vector<GMLToken> > &array_) :
	GMLOperator(stack), m_array(array_)
	{

		m_name = "get";
	};

	//------------------------------------------------------------------

	~GetOperator(){};

	//------------------------------------------------------------------
	void execute() const
	{

		GMLToken operand1;
		GMLToken operand2;
		if(m_stack.empty())
			throw std::runtime_error( "ERROR get: Stack is empty" );

		operand2 = m_stack.back();
		m_stack.pop_back();

		if(m_stack.empty())
		  throw std::runtime_error( "ERROR get: Stack is empty" );

		operand1 = m_stack.back();
		m_stack.pop_back();		

		if (( operand1.m_type == ARRAY) &&
			( operand2.m_type == INTEGER))
		{
			int index = operand2.m_int[0];
			int size = m_array[operand1.m_int[0]].size() - 1;
			
			if( (size < index) || (index < 0))
			{
			  throw std::runtime_error(  "ERROR get: Index error");
			}
			GMLToken result = m_array[operand1.m_int[0]][size - index];

			m_stack.push_back(result);
			
		}
   	};
	//------------------------------------------------------------------
private:
	std::vector<std::vector<GMLToken> > &m_array;
};

#endif  // GETOPERATOR
