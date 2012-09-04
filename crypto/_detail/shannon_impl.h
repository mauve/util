/* $Id: $ */
/* Shannon: Shannon stream cipher and MAC header files */

/*
THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND AGAINST
INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef BASE_SHANNON_H_
#define BASE_SHANNON_H_

#include <limits.h>
#if __STDC_VERSION__ >= 199901
#include <stdint.h>
#endif

#define SHANNON_N 16
#define SHANNON_WORDSIZE 32
#define SHANNON_UCHAR unsigned char

#if __STDC_VERSION__ >= 199901
#define SHANNON_WORD uint32_t
#define SHANNON_WORD_MAX UINT32_MAX
#elif UINT_MAX >= 0xffffffff
#define SHANNON_WORD unsigned int
#define SHANNON_WORD_MAX UINT_MAX
#else
#define SHANNON_WORD unsigned long
#define SHANNON_WORD_MAX ULONG_MAX
#endif

typedef struct {
    SHANNON_WORD  R[SHANNON_N];   /* Working storage for the shift register */
    SHANNON_WORD  CRC[SHANNON_N];   /* Working storage for CRC accumulation */
    SHANNON_WORD  initR[SHANNON_N]; /* saved register contents */
    SHANNON_WORD  konst;    /* key dependent semi-constant */
    SHANNON_WORD  sbuf;   /* encryption buffer */
    SHANNON_WORD  mbuf;   /* partial word MAC buffer */
    int   nbuf;   /* number of part-word stream bits buffered */
} shn_ctx;

/* interface definitions */
void shn_key(shn_ctx *c, SHANNON_UCHAR key[], int keylen);  /* set key */
void shn_nonce(shn_ctx *c, SHANNON_UCHAR nonce[], int nlen);  /* set Init Vector */
void shn_stream(shn_ctx *c, SHANNON_UCHAR *buf, int nbytes);  /* stream cipher */
void shn_maconly(shn_ctx *c, SHANNON_UCHAR *buf, int nbytes); /* accumulate MAC */
void shn_encrypt(shn_ctx *c, SHANNON_UCHAR *buf, int nbytes); /* encrypt + MAC */
void shn_decrypt(shn_ctx *c, SHANNON_UCHAR *buf, int nbytes); /* decrypt + MAC */
void shn_finish(shn_ctx *c, SHANNON_UCHAR *buf, int nbytes);  /* finalise MAC */

#endif  // BASE_SHANNON_H_
