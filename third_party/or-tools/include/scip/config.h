#ifndef __CONFIG_H__
#define __CONFIG_H__

#define CMAKE_BUILD_TYPE "Release"
#define SCIP_VERSION_MAJOR 9
#define SCIP_VERSION_MINOR 0
#define SCIP_VERSION_PATCH 0
#define SCIP_VERSION_SUB 0
#define SCIP_VERSION_API 114
/* #undef BMS_NOBLOCKMEM */
/* #undef SCIP_NOBUFFERMEM */
/* #undef WITH_DEBUG_SOLUTION */
/* #undef SCIP_NO_SIGACTION */
/* #undef SCIP_NO_STRTOK_R */
/* #undef TPI_NONE */
#define TPI_TNY
/* #undef TPI_OMP */
#define SCIP_THREADSAFE
#define WITH_SCIPDEF
/* #undef SCIP_WITH_LAPACK */
/* #undef SCIP_WITH_PAPILO */
/* #undef SCIP_WITH_ZLIB */
/* #undef SCIP_WITH_READLINE */
/* #undef SCIP_WITH_GMP */
/* #undef SCIP_WITH_LPSCHECK */
/* #undef SCIP_WITH_ZIMPL */
/* #undef SCIP_WITH_AMPL */
#define SCIP_ROUNDING_FE
/* #undef SCIP_ROUNDING_FP */
/* #undef SCIP_ROUNDING_MS */

#endif
