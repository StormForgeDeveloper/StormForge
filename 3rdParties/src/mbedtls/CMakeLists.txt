

include_directories(AFTER 
	./
	mbedtls-2.16.0/include
	mbedtls-2.16.0/library
)


set(src_crypto
    mbedtls-2.16.0/library/aes.c
    mbedtls-2.16.0/library/aesni.c
    mbedtls-2.16.0/library/arc4.c
    mbedtls-2.16.0/library/aria.c
    mbedtls-2.16.0/library/asn1parse.c
    mbedtls-2.16.0/library/asn1write.c
    mbedtls-2.16.0/library/base64.c
    mbedtls-2.16.0/library/bignum.c
    mbedtls-2.16.0/library/blowfish.c
    mbedtls-2.16.0/library/camellia.c
    mbedtls-2.16.0/library/ccm.c
    mbedtls-2.16.0/library/chacha20.c
    mbedtls-2.16.0/library/chachapoly.c
    mbedtls-2.16.0/library/cipher.c
    mbedtls-2.16.0/library/cipher_wrap.c
    mbedtls-2.16.0/library/cmac.c
    mbedtls-2.16.0/library/ctr_drbg.c
    mbedtls-2.16.0/library/des.c
    mbedtls-2.16.0/library/dhm.c
    mbedtls-2.16.0/library/ecdh.c
    mbedtls-2.16.0/library/ecdsa.c
    mbedtls-2.16.0/library/ecjpake.c
    mbedtls-2.16.0/library/ecp.c
    mbedtls-2.16.0/library/ecp_curves.c
    mbedtls-2.16.0/library/entropy.c
    mbedtls-2.16.0/library/entropy_poll.c
    mbedtls-2.16.0/library/error.c
    mbedtls-2.16.0/library/gcm.c
    mbedtls-2.16.0/library/havege.c
    mbedtls-2.16.0/library/hkdf.c
    mbedtls-2.16.0/library/hmac_drbg.c
    mbedtls-2.16.0/library/md.c
    mbedtls-2.16.0/library/md2.c
    mbedtls-2.16.0/library/md4.c
    mbedtls-2.16.0/library/md5.c
    mbedtls-2.16.0/library/md_wrap.c
    mbedtls-2.16.0/library/memory_buffer_alloc.c
    mbedtls-2.16.0/library/nist_kw.c
    mbedtls-2.16.0/library/oid.c
    mbedtls-2.16.0/library/padlock.c
    mbedtls-2.16.0/library/pem.c
    mbedtls-2.16.0/library/pk.c
    mbedtls-2.16.0/library/pk_wrap.c
    mbedtls-2.16.0/library/pkcs12.c
    mbedtls-2.16.0/library/pkcs5.c
    mbedtls-2.16.0/library/pkparse.c
    mbedtls-2.16.0/library/pkwrite.c
    mbedtls-2.16.0/library/platform.c
    mbedtls-2.16.0/library/platform_util.c
    mbedtls-2.16.0/library/poly1305.c
    mbedtls-2.16.0/library/ripemd160.c
    mbedtls-2.16.0/library/rsa.c
    mbedtls-2.16.0/library/rsa_internal.c
    mbedtls-2.16.0/library/sha1.c
    mbedtls-2.16.0/library/sha256.c
    mbedtls-2.16.0/library/sha512.c
    mbedtls-2.16.0/library/threading.c
    mbedtls-2.16.0/library/timing.c
    mbedtls-2.16.0/library/version.c
    mbedtls-2.16.0/library/version_features.c
    mbedtls-2.16.0/library/xtea.c
)

set(src_x509
    mbedtls-2.16.0/library/certs.c
    mbedtls-2.16.0/library/pkcs11.c
    mbedtls-2.16.0/library/x509.c
    mbedtls-2.16.0/library/x509_create.c
    mbedtls-2.16.0/library/x509_crl.c
    mbedtls-2.16.0/library/x509_crt.c
    mbedtls-2.16.0/library/x509_csr.c
    mbedtls-2.16.0/library/x509write_crt.c
    mbedtls-2.16.0/library/x509write_csr.c
)

set(src_tls
    mbedtls-2.16.0/library/debug.c
    mbedtls-2.16.0/library/net_sockets.c
    mbedtls-2.16.0/library/ssl_cache.c
    mbedtls-2.16.0/library/ssl_ciphersuites.c
    mbedtls-2.16.0/library/ssl_cli.c
    mbedtls-2.16.0/library/ssl_cookie.c
    mbedtls-2.16.0/library/ssl_srv.c
    mbedtls-2.16.0/library/ssl_ticket.c
    mbedtls-2.16.0/library/ssl_tls.c
)





add_library(mbedtls ${src_crypto} ${src_x509} ${src_tls})


install (TARGETS mbedtls
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)



