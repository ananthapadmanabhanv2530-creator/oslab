#include <stdio.h>

#define MAX 100

// --------------------------------------------------
// FIFO PAGE REPLACEMENT
// --------------------------------------------------
int fifo(int ref[], int n, int frames)
{
   int frame[MAX];
   int pointer = 0;     // Points to oldest page
   int faults = 0;

   // Initialize frames as empty
   for(int i=0;i<frames;i++)
       frame[i] = -1;

   // Traverse reference string
   for(int i=0;i<n;i++)
   {
       int page = ref[i];
       int found = 0;

       // Check if page already in frame (HIT)
       for(int j=0;j<frames;j++)
       {
           if(frame[j] == page)
           {
               found = 1;
               break;
           }
       }

       // If page not found → PAGE FAULT
       if(!found)
       {
           frame[pointer] = page;

           // Move pointer circularly
           pointer = (pointer + 1) % frames;

           faults++;
       }
   }

   return faults;
}


// --------------------------------------------------
// LRU PAGE REPLACEMENT
// --------------------------------------------------
int lru(int ref[], int n, int frames)
{
   int frame[MAX];
   int recent[MAX];   // Stores last used time
   int faults = 0;

   // Initialize
   for(int i=0;i<frames;i++)
   {
       frame[i] = -1;
       recent[i] = -1;
   }

   // Traverse reference string
   for(int i=0;i<n;i++)
   {
       int page = ref[i];
       int found = 0;

       // Check HIT
       for(int j=0;j<frames;j++)
       {
           if(frame[j] == page)
           {
               found = 1;
               recent[j] = i;  // Update last used time
               break;
           }
       }

       // If MISS → Replace least recently used page
       if(!found)
       {
           int lruIndex = 0;

           for(int j=1;j<frames;j++)
           {
               if(recent[j] < recent[lruIndex])
                   lruIndex = j;
           }

           frame[lruIndex] = page;
           recent[lruIndex] = i;

           faults++;
       }
   }

   return faults;
}


// --------------------------------------------------
// OPTIMAL PAGE REPLACEMENT
// --------------------------------------------------
int optimal(int ref[], int n, int frames)
{
   int frame[MAX];
   int faults = 0;

   // Initialize frames
   for(int i=0;i<frames;i++)
       frame[i] = -1;

   // Traverse reference string
   for(int i=0;i<n;i++)
   {
       int page = ref[i];
       int found = 0;

       // Check HIT
       for(int j=0;j<frames;j++)
       {
           if(frame[j] == page)
           {
               found = 1;
               break;
           }
       }

       // If MISS → Replace farthest future page
       if(!found)
       {
           int replaceIndex = -1;
           int farthest = -1;

           for(int j=0;j<frames;j++)
           {
               int k;

               for(k=i+1;k<n;k++)
               {
                   if(frame[j] == ref[k])
                       break;
               }

               // Page never used again
               if(k == n)
               {
                   replaceIndex = j;
                   break;
               }

               // Select page used farthest in future
               if(k > farthest)
               {
                   farthest = k;
                   replaceIndex = j;
               }
           }

           frame[replaceIndex] = page;
           faults++;
       }
   }

   return faults;
}


// --------------------------------------------------
// MAIN FUNCTION
// --------------------------------------------------
int main()
{
   int ref[MAX];
   int n, frames;

   printf("Enter number of page references: ");
   scanf("%d",&n);

   printf("Enter the page reference string:\n");
   for(int i=0;i<n;i++)
       scanf("%d",&ref[i]);

   printf("Enter number of frames: ");
   scanf("%d",&frames);

   printf("\nPage Reference String: ");
   for(int i=0;i<n;i++)
       printf("%d ",ref[i]);

   printf("\nFrame Size = %d\n",frames);

   printf("\n--- Page Replacement Results ---\n");

   printf("FIFO Page Faults : %d\n", fifo(ref,n,frames));
   printf("LRU  Page Faults : %d\n", lru(ref,n,frames));
   printf("OPT  Page Faults : %d\n", optimal(ref,n,frames));

   return 0;
