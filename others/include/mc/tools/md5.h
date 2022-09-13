#ifndef MC_TOOLS_MD5_H
#define MC_TOOLS_MD5_H

#include <string>

#include <openssl/evp.h>

namespace mc::tools
{
    inline void MD5Sum(const char *input, unsigned int size, unsigned char *output)
    {
        EVP_MD_CTX *mdctx{EVP_MD_CTX_new()};
        if (!mdctx)
        {
            return;
        }

        if (1 != EVP_DigestInit_ex(mdctx, EVP_md5(), nullptr))
        {
            return;
        }

        if (1 != EVP_DigestUpdate(mdctx, input, size))
        {
            return;
        }

        // if ((*digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()))) == NULL)
        //     handleErrors();

        if (1 != EVP_DigestFinal_ex(mdctx, output, &size))
        {
            return;
        }
        EVP_MD_CTX_free(mdctx);
    }
    inline void MD5Sum(const std::string &input, unsigned char *output)
    {
        MD5Sum(input.data(), input.size(), output);
    }
}

#endif
