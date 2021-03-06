/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "main.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

struct do_circulant *
circulant_1(do_circulant *argp, CLIENT *clnt)
{
	static struct do_circulant clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, circulant,
		(xdrproc_t) xdr_do_circulant, (caddr_t) argp,
		(xdrproc_t) xdr_do_circulant, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
