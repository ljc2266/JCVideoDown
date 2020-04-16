/**//* 

    Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All

    rights reserved.



    License to copy and use this software is granted provided that it

    is identified as the "RSA Data Security, Inc. MD5 Message-Digest

    Algorithm" in all material mentioning or referencing this software

    or this function.



    License is also granted to make and use derivative works provided

    that such works are identified as "derived from the RSA Data

    Security, Inc. MD5 Message-Digest Algorithm" in all material

    mentioning or referencing the derived work.



    RSA Data Security, Inc. makes no representations concerning either

    the merchantability of this software or the suitability of this

    software for any particular purpose. It is provided "as is"

    without express or implied warranty of any kind.



    These notices must be retained in any copies of any part of this

    documentation and/or software.

*/

// MD5Crypt.h: interface for the CMD5Crypt class.

// Author:WSAATool

/**///////////////////////////////////////////////////////////////////////



#if !defined(AFX_MD5CRYPT_H__8D1E322D_1EF6_4954_A9CF_BAD85BDD1E90__INCLUDED_)

#define AFX_MD5CRYPT_H__8D1E322D_1EF6_4954_A9CF_BAD85BDD1E90__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000



class CMD5Crypt  

{

private:

    /**//* MD5 context. */

    typedef struct {

        UINT  state[4];        /**//* state (ABCD) */

        UINT  count[2];        /**//* number of bits, modulo 2^64 (lsb first) */

        UCHAR buffer[64];      /**//* input buffer */

    }MD5_CTX;

    MD5_CTX *context;



public:

    CMD5Crypt();

    virtual ~CMD5Crypt();

    //c风格接口,功能和rfc1321中原文的实现代码接口相同

    void Init(void);

    void Update(unsigned char *input, unsigned int inputLen);

    void Final(unsigned char digest[16]);

    //MFC风格接口,可以直接使用,不需要调用Init,Update和Final接口

    VOID GetMd5String(OUT CString &strMD5,IN char *input,IN int inputlen);

    VOID GetMd5String(OUT CString &strMD5,IN CString strInput);



private:

 VOID Encode(unsigned char *output,unsigned int *input,unsigned int len);

 VOID Decode(unsigned int *output,unsigned char *input,unsigned int len);

 VOID MD5Transform(unsigned int state[4],unsigned char block[64]);

};

#endif // !defined(AFX_MD5CRYPT_H__8D1E322D_1EF6_4954_A9CF_BAD85BDD1E90__INCLUDED_)