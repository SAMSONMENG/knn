#include <hls_stream.h>
#include "Data16.h"
#include "Data8.h"
#include <math.h>
#include <ap_int.h>
#include <ap_axi_sdata.h>



typedef ap_axis<32,2,5,6> unit32;
using namespace std;


//volatile int*input;
//volatile int*output;
void knn3(hls::stream<unit32>&inStream,hls::stream<unit32> &outStream,  int gain);
//void knn1(volatile int*input,volatile int*output);
int main()
{
hls::stream<unit32> inputStream;
hls::stream<unit32> outputStream;
int indi[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int sum[10][2]={0};
int di=16;
int re=0;// only use in row 34-37
int refer[16];//reference  16 knn in this array
int index=0;
//volatile int* in;
//volatile int* res;
//int a;
//int di = 16;
unit32 valIn;
unit32 out;
for(int i=0;i<di;i++){   // record first 16 numbers as reference.

	refer[i]=myData[re*di+i];
}


for(int j=1;j<10;j++)// 9 nearest, j=0 is the first row, so start at 1.
{

//calculate knn distance
for(int i=0;i<di;i++)
{

	valIn.data = i;
	valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	inputStream<<valIn;
	valIn.data = refer[i];
	valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	inputStream<<valIn;;
	valIn.data = myData[i+di*j];
	valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	inputStream<<valIn;;
	knn3(inputStream,outputStream,1);
	outputStream.read(out);
	indi[i]=out.data;
}
    printf("%u, %u\n",indi[0],indi[1]);
    for(int k=0;k<di;k++){
    	valIn.data = 17;
    	valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
    	inputStream<<valIn;
    	valIn.data = sum[j-1][1];
    	valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
    	inputStream<<valIn;;
    	valIn.data = indi[k];
    	valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
    	inputStream<<valIn;
    	knn3(inputStream,outputStream,1);
    	outputStream.read(out);
        sum[j-1][1]=out.data;
    }
     sum[j-1][0]=j-1;

}

 for(int i=0;i<9;i++)
 printf("%u nearest index is %u \n",sum[i][0],(int)sum[i][1]);

//
 for(int i=0;i<9;i++)
 {

    int compare=0;
	valIn.data = 100;
	valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	inputStream<<valIn;
	valIn.data = sum[index][1];
	valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	inputStream<<valIn;
	valIn.data = sum[i][1];;
	valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	inputStream<<valIn;
	knn3(inputStream,outputStream,1);
	outputStream.read(out);
	compare=out.data;
	if(compare==sum[index][1])
		continue;
	else
		index=i;
}

 printf("largest index:%u\n",sum[index][1]);

 for(int s=10;s<15;s++)
 {
	 sum[9][1]=0;
	 for(int i=0;i<di;i++)
	 {
			valIn.data = i;
			valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
			inputStream<<valIn;
			valIn.data = refer[i];
			valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
			inputStream<<valIn;;
			valIn.data = myData[i+di*s];
			valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
			inputStream<<valIn;;
			knn3(inputStream,outputStream,1);
			outputStream.read(out);
			indi[i]=out.data;
	 }
	     for(int k=0;k<di;k++){
	    	 valIn.data = 17;
	    	 valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	    	 inputStream<<valIn;
	    	 valIn.data = sum[9][1];
	    	 valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	    	 inputStream<<valIn;;
	    	 valIn.data = indi[k];
	    	 valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	    	 inputStream<<valIn;
	    	 knn3(inputStream,outputStream,1);
	    	 outputStream.read(out);
	    	 sum[9][1]=out.data;
	     }
	     sum[9][0]=s-1;
         if(sum[9][0]==1637||sum[9][0]==54804||sum[9][0]==12259||sum[9][0]==22678)
        	 for(int z=0;z<16;z++)
        	 printf(" index:%u, distance:%u\n",sum[9][0],indi[z]);
	     int compare=0;
	     valIn.data = 100;
	     valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	     inputStream<<valIn;
	     valIn.data = sum[9][1];
	     valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	     inputStream<<valIn;
	     valIn.data = sum[index][1];
	     valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	     inputStream<<valIn;
	     knn3(inputStream,outputStream,1);
	 	 outputStream.read(out);
	 	 compare=out.data;
	     if(compare == sum[index][1])
	     {
	    	sum[index][1]=sum[9][1];
	        sum[index][0]=sum[9][0];
	        for(int i=0;i<9;i++)
	         {

	        	int compare=0;
	        	valIn.data = 100;
	        	valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	        	inputStream<<valIn;
	        	valIn.data = sum[index][1];
	        	valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	        	inputStream<<valIn;
	        	valIn.data = sum[i][1];
	            valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	        	inputStream<<valIn;
	        	knn3(inputStream,outputStream,1);
	        	outputStream.read(out);
	        	compare=out.data;
	        	if(compare==sum[index][1])
	        		continue;
	        	else
	        		index=i;
	        }
	     }
	     else{
	    	continue;
	     }

 }

 for(int i=0;i<9;i++)
	 printf("%u nearest distance is %u\n",sum[i][0],sum[i][1]);

}


/*
a=sizeof(myData)/4;
printf("total: %u \n",a);
int b=a/di;
unit32 valIn;
valIn.data = b;
valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
inputStream<<valIn;

valIn.data = di;
valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
inputStream<<valIn;

*/
//for(int i=0;i<144;i++)
//memcpy(&in,&myData1,144*sizeof(int));

/*
for(long int idx=0;idx<b;idx++)
{
	;
	for(int i=0;i<16;i++)
	{
	memcpy(&index[i],&myData[idx*di+i],sizeof(myData[0]));
	unit32 valIn;
	valIn.data = index[i];
	valIn.keep=1;valIn.strb=1;valIn.user=1;valIn.id=0;valIn.dest=0;
	inputStream<<valIn;
	}
}
*/
//knn1(in,res);//use the function

//for(int i=0;i<10;i++)
//	printf("k nearest index is %u \n",(unsigned int)res[i]);



/*
for (int k=1;k<10;k++)
	 {
	    unit64 out;
		outputStream.read(out);
		printf("k nearest index is %u \n",(unsigned int)out.data);
	 }

	 for (int l=1;l<10;l++)
	 {
		unit64 out1;
		outputStream.read(out1);
		printf("k nearest distance is %u \n",(unsigned int)out1.data);
	 }//output the results
return 0;
}
*/
/*knn16(inputStream,outputStream,di);
for(int idxOut=0;idxOut < 9;idxOut++)
{
	outStdCh valOut;
	outStdCh c;
	valOut.keep=1;valOut.strb=1;valOut.user=1;valOut.id=0;valOut.dest=0;
	outputStream.read(valOut);

	printf("Distances is %u \n",(unsigned long)valOut.data);


}
return 0;
}
*/
