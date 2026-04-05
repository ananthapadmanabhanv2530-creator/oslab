#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
for(int i=0;i<n-1;i++)
for(int j=i+1;j<n;j++)
if(arr[i] > arr[j]) {
int temp = arr[i];
arr[i] = arr[j];
arr[j] = temp;
}}

int SSTF(int req[], int n, int head) {
int visited[50] = {0}, movement = 0;
for(int i=0;i<n;i++) {
int min = 100000, index = -1;
for(int j=0;j<n;j++) {
if(!visited[j]) {
int dist = abs(req[j] - head);
if(dist < min) { min = dist; index = j; }
}}
movement += min;
head = req[index];
visited[index] = 1;
}
return movement;
}

int LOOK(int req[], int n, int head) {
int movement = 0, pos;
sort(req,n);
for(int i=0;i<n;i++) if(req[i] > head) { pos = i; break; }
for(int i=pos;i<n;i++) { movement += abs(head - req[i]); head = req[i]; }
for(int i=pos-1;i>=0;i--) { movement += abs(head - req[i]); head = req[i]; }
return movement;
}

int CSCAN(int req[], int n, int head, int disk_size) {
int movement = 0, pos;
sort(req,n);
for(int i=0;i<n;i++) if(req[i] > head) { pos = i; break; }
for(int i=pos;i<n;i++) { movement += abs(head - req[i]); head = req[i]; }
movement += abs(head - (disk_size-1));
head = 0; // Jump
for(int i=0;i<pos;i++) { movement += abs(head - req[i]); head = req[i]; }
return movement;
}

int main() {
int n, head, disk_size, req[50];
printf("Enter number of requests: "); scanf("%d",&n);
printf("Enter requests:\n"); for(int i=0;i<n;i++) scanf("%d",&req[i]);
printf("Enter head position: "); scanf("%d",&head);
printf("Enter disk size: "); scanf("%d",&disk_size);
printf("SSTF: %d\nLOOK: %d\nC-SCAN: %d\n", SSTF(req,n,head), LOOK(req,n,head), CSCAN(req,n,head,disk_size));
return 0;
}
