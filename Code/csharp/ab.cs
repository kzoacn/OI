using System;
using System.Collections;
namespace ab{
	class pro{
		static int read(){
			int res=0;char c=Convert.ToChar(Console.Read());
			while(!Char.IsDigit(c))c=Convert.ToChar(Console.Read());
			while(Char.IsDigit(c)){res=res*10+c-'0';c=Convert.ToChar(Console.Read());}
			return res;
		}
		static void Main(){
			int k=read(),n=read(),w=read();
			int ans=0;
			for(int i=1;i<=w;i++)ans+=i*k;
			Console.WriteLine(Math.Max(ans-n,0));
		}
	}
}
