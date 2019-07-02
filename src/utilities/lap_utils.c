#define HYPRE_TIMING
/* 
we have to define HYPRE_TIMING
to ensure the right defs are made available by headers

we have to NOT define HYPRE_TIMING_GLOBALS,
to avoid duplicate symbol hypre_global_timing
 */
#include "_hypre_utilities.h"
#include "timing.h"
#include "lap_utils.h"



/* 
From looking at 

HYPRE_IJVectorPrint( HYPRE_IJVector  vector,
                     const char     *filename )
in HYPRE_IJVector.c

and

hypre_PrintTiming( const char     *heading,
                   MPI_Comm        comm  )
in timing.c

 */

HYPRE_Int
hypre_GetTiming(const char *heading, const char *filename,
                MPI_Comm comm)
{
   HYPRE_Int  ierr = 0;

   HYPRE_Real  local_wall_time;
   HYPRE_Real  local_cpu_time;
   HYPRE_Real  wall_time;
   HYPRE_Real  cpu_time;
   HYPRE_Real  wall_mflops;
   HYPRE_Real  cpu_mflops;

   HYPRE_Int     i;
   HYPRE_Int     myrank;

   FILE           *file;

   if (hypre_global_timing == NULL)
      return ierr;

   hypre_MPI_Comm_rank(comm, &myrank );

   /* print heading */
   if (myrank == 0)
   {
      hypre_printf("=============================================\n");
      hypre_printf("%s:\n", heading);
      hypre_printf("writing timing info to file %s:\n", filename);
      hypre_printf("=============================================\n");
   }

   for (i = 0; i < (hypre_global_timing -> size); i++)
   {
      if (hypre_TimingNumRegs(i) > 0)
      {
         local_wall_time = hypre_TimingWallTime(i);
         local_cpu_time  = hypre_TimingCPUTime(i);
         hypre_MPI_Allreduce(&local_wall_time, &wall_time, 1,
                       hypre_MPI_REAL, hypre_MPI_MAX, comm);
         hypre_MPI_Allreduce(&local_cpu_time, &cpu_time, 1,
                       hypre_MPI_REAL, hypre_MPI_MAX, comm);

         if (myrank == 0)
         {
            
            hypre_printf("%s:\n", hypre_TimingName(i));

            /* print wall clock info */
            hypre_printf("  wall clock time = %f seconds\n", wall_time);
            if (wall_time)
               wall_mflops = hypre_TimingFLOPS(i) / wall_time / 1.0E6;
            else
               wall_mflops = 0.0;
            hypre_printf("  wall MFLOPS     = %f\n", wall_mflops);

            /* print CPU clock info */
            hypre_printf("  cpu clock time  = %f seconds\n", cpu_time);
            if (cpu_time)
               cpu_mflops = hypre_TimingFLOPS(i) / cpu_time / 1.0E6;
            else
               cpu_mflops = 0.0;
            hypre_printf("  cpu MFLOPS      = %f\n\n", cpu_mflops);
         }
      }
   }

   if (myrank == 0){
      if ((file = fopen(filename, "w")) == NULL)
      {
         hypre_error_in_arg(2);
         return hypre_error_flag; /* TODOLOW: I don't know if this makes sense at all*/
      }
      hypre_fprintf(file, "%e\n", wall_time);

      fclose(file);
   }

   return ierr;
}


HYPRE_Int
hypre_PrintRealToFile(const char *heading, const char *filename, HYPRE_Real datum,
                MPI_Comm comm)
{
   HYPRE_Int  ierr = 0;
   HYPRE_Int     myrank;

   FILE           *file;

   hypre_MPI_Comm_rank(comm, &myrank );

   /* print heading */
   if (myrank == 0)
   {
      hypre_printf("=============================================\n");
      hypre_printf("%s:\n", heading);
      hypre_printf("writing datum to file %s:\n", filename);
      hypre_printf("value : %e\n", datum);
      hypre_printf("=============================================\n");

      if ((file = fopen(filename, "w")) == NULL)
      {
         hypre_error(1);
         return hypre_error_flag; /* TODOLOW: I don't know if this makes sense at all*/
      }
      hypre_fprintf(file, "%e\n", datum);

      fclose(file);

      return ierr;
   } else {
      /* should only be called w myrank == 0 proc */
      hypre_error(1);
      return hypre_error_flag; /* TODOLOW: I don't know if this makes sense at all*/
   }
}