#ifndef ZAMARA_EXCEPTION_EXCEPTION_H_
#define ZAMARA_EXCEPTION_EXCEPTION_H_

#include <string>
#include <exception>

namespace zamara {
	namespace exception {

class ZamaraException : public std::exception {
 public:
	enum ExceptionType {
		FILE_NOT_FOUND	    	= 100,
		FILE_NOT_MPQ	      	= 110,
    UNKNOWN_COMPRESSION 	= 200,
    UNKNOWN_SERIALIZATION	= 300,
    MPQ_FILE_NOT_FOUND		=	400
	};

	ZamaraException(const std::string& message, ExceptionType type) throw()
		: exception_type_(type), message_(message) { }
	ZamaraException() throw() { }
	~ZamaraException() throw() { }

	ExceptionType exception_type() { return exception_type_; }
	std::string message() { return message_; }

 private:
        ExceptionType exception_type_;
        std::string message_;
};

	}
}

#endif // ZAMARA_EXCEPTION_EXCEPTION_H_
