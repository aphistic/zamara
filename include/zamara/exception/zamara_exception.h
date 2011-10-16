#ifndef _ZAMARA_EXCEPTION_H
#define _ZAMARA_EXCEPTION_H

#include <string>
#include <exception>

namespace zamara
{
	namespace exception
	{

class ZamaraException : public std::exception
{
public:
	enum ExceptionType
	{
		FILE_NOT_FOUND	= 100,
		FILE_NOT_MPQ	= 110
	};

	ZamaraException(const std::string& message, ExceptionType type) throw()
		: m_message(message), m_exType(type) { }
	ZamaraException() throw() { }
	~ZamaraException() throw() { }

	ExceptionType getType() { return m_exType; }
	std::string getMessage() { return m_message; }

private:
        ExceptionType m_exType;
        std::string m_message;

};

	}
}
#endif
