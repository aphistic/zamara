/* Zamara Library
 * Copyright (c) 2011, Erik Davidson
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

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
