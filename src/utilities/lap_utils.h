
/******************************************************************************
 *
 * Header file structs etc that Laplacians need for testing or using Hypre 
 *
 *****************************************************************************/
#include "_hypre_utilities.h" 
/* RK 2019 not sure if I need that include? but seems to resolve a compile issue with HYPRE_Real not defined */

typedef struct
{
   HYPRE_Real  wall_time;
   HYPRE_Real  cpu_time;
   HYPRE_Real  flops;
   
   HYPRE_Real   wall_count;
   HYPRE_Real   CPU_count;
   HYPRE_Real   FLOP_count;

} lapl_hypre_TimingType;


/* lap_utils.c */
HYPRE_Int hypre_GetTiming( const char *heading , const char *filename, MPI_Comm comm );

HYPRE_Int
hypre_PrintRealToFile(const char *heading, const char *filename, HYPRE_Real datum,
                MPI_Comm comm);