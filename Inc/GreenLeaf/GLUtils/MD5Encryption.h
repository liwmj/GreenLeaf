/*
 * MD5Encryption.h
 *
 *  Created on: Nov 26, 2014
 *      Author: Mason
 */

#ifndef MD5ENCRYPTION_H
#define MD5ENCRYPTION_H

#define HS_ENTYPE_NONE          (0)
#define HS_ENTYPE_MD5           (1)
#define HS_ENTYPE_MD5EX         (2)

namespace GreenLeaf {
namespace GLUtils {

class MD5Encryption
{
public:
    static MD5Encryption& instance();

    void digest_md5(unsigned char* buffer, int buffer_len, unsigned char* digest);

private:
    typedef struct _MD5_CTX {
        unsigned long i[2]; /* number of _bits_ handled mod 2^64 */
        unsigned long buf[4]; /* scratch buffer */
        unsigned char in[64]; /* input buffer */
        unsigned char digest[32]; /* actual digest after MD5Final call*/
    } MD5_CTX;

    void MD5Init(MD5_CTX* mdContext);
    void MD5Update(MD5_CTX* mdContext, unsigned char* inBuf, unsigned int inLen);
    void MD5Final(MD5_CTX* mdContext);
    void transform(unsigned long* buf, unsigned long* in);

};

} } // GreenLeaf::GLUtils

#endif // MD5ENCRYPTION_H

