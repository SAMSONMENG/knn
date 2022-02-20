#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <string.h> // memcpy
#include <stdlib.h> //realloc

typedef ap_axis<32,2,5,6> unit32;

void knn3(hls::stream<unit32>&inStream,hls::stream<unit32> &outStream, int gain)
{
#pragma HLS INTERFACE axis port=outStream
#pragma HLS INTERFACE axis port=inStream

#pragma HLS INTERFACE S_axilite port=gain bundle=CRTL_BUS
#pragma HLS INTERFACE S_axilite port=return bundle=CRTL_BUS


int index;
int dim;
int a1=0;
int a2=0;


    unit32 val_in1;
	unit32 val_in2;
	unit32 val_in3;
	unit32 val_out;
	val_in1= inStream.read();
	int x=val_in1.data;
	val_in2= inStream.read();
	int y=val_in2.data;
	val_in3= inStream.read();
	int z=val_in3.data;
    if(x<=16){
    	   a2= (int)(y/100-z/100)*(y/100-z/100)/100;
           val_out.data=a2;
           outStream.write(val_out);
    	}
    else if(x>16&&x<40)
    {
    	a2=y+z;
    	val_out.data=a2;
    	outStream.write(val_out);
    }

    else {
    	if(y<z){
    		val_out.data=z;
    		outStream.write(val_out);
    	}
    	else{
    		val_out.data=y;
    		outStream.write(val_out);
    	}
    }




}

/*
	if(idx == 10)
	{
		for(int i=0;i<10;i++)
		{
			for(int j=0;j<10-i;j++)
			{
				if(res[j]>res[j+1])
				{
					temp=res[j];
					res[j]=res[j+1];
					res[j+1]=temp;
					temp1=d[j];
				    d[j]=d[j+1];
					d[j+1]=temp1;
				}
			}
		}
	}
*/
/*
	else if(idx > 10)
	{
		if(a < res[9])
		{
			res[9] = a;
			d[9]=c[idx];

			for(int i=0;i<10;i++)
			{
				for(int j=0;j<10-i;j++)
				{
					if(res[j]>res[j+1])
					{
						temp=res[j];
						res[j]=res[j+1];
						res[j+1]=temp;
						temp1=d[j];
					    d[j]=d[j+1];
						d[j+1]=temp1;
					}//sort the least 9 distances and index
				}
			}
		}
	}
*/

//pass the input in and calculate, let the first 16 be the Y and others are X, and calculate the distances

/*

for(int e=1;e<10;e++)
{

	outStdCh valOut;

		valOut.data=res[e];

		valOut.keep = valIn.keep;
		valOut.strb = valIn.strb;
		valOut.user = valIn.user;
		valOut.id = valIn.id;
		valOut.dest = valIn.dest;
		valOut.last = valIn.last;
		outStream.write(valOut);

}


*/
