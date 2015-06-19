import java.io.*;
import java.util.*;
public class h {
	static Long hash(Long h) {
		h ^= (h >>> 20) ^ (h >>> 12);
		return h ^ (h >>> 7) ^ (h >>> 4);
	}
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader( new InputStreamReader( System.in ) );
        HashSet<Long> hashset = new HashSet<Long>(0,0.75F);
//        System.out.println(hashset.map.hashSeed);
        for (String x = in.readLine(); x != null ; x = in.readLine())
         //for(int x=1;x<=100;x++)
         {
         	
           hashset.add( Long.parseLong(x) );        
	    //	System.out.println((new Long(x*2000000000)).hashCode());
	    	//System.out.println(hash((new Long(x*2000000000))));
        }
    }
}
