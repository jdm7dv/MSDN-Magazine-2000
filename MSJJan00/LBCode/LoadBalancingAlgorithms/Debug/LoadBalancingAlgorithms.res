        џџ  џџ                  T      џџ џџ     0 	        T4   V S _ V E R S I O N _ I N F O     Няў               ?                        Д   S t r i n g F i l e I n f o      0 4 0 9 0 4 B 0        C o m p a n y N a m e     f   F i l e D e s c r i p t i o n     L o a d B a l a n c i n g A l g o r i t h m s   M o d u l e     6   F i l e V e r s i o n     1 ,   0 ,   0 ,   1     P   I n t e r n a l N a m e   L o a d B a l a n c i n g A l g o r i t h m s   B   L e g a l C o p y r i g h t   C o p y r i g h t   1 9 9 9     `   O r i g i n a l F i l e n a m e   L o a d B a l a n c i n g A l g o r i t h m s . D L L   ^   P r o d u c t N a m e     L o a d B a l a n c i n g A l g o r i t h m s   M o d u l e     :   P r o d u c t V e r s i o n   1 ,   0 ,   0 ,   1     (    O L E S e l f R e g i s t e r     D    V a r F i l e I n f o     $    T r a n s l a t i o n     	А1  0   R E G I S T R Y   џџe       0	        HKCR
{
    NoRemove 'Component Categories'
    {
        {9FDC5DE0-E180-11d2-B72C-00A0CC212296}
        {
            val 409 = s 'Load Balanced Classes'
        }
        {9FDC5DE1-E180-11d2-B72C-00A0CC212296}
        {
            val 409 = s 'Load Balancing Algorithms'
        }
    }
}
   =  0   R E G I S T R Y   џџf       0	        HKCR
{
	LoadBalancingAlgorithms.Random.1 = s 'Random Algorithm'
	{
		CLSID = s '{3C406C5E-E3B1-11D2-8117-00E09801FDBE}'
	}
	LoadBalancingAlgorithms.Random = s 'Random Algorithm'
	{
		CLSID = s '{3C406C5E-E3B1-11D2-8117-00E09801FDBE}'
		CurVer = s 'LoadBalancingAlgorithms.Random.1'
	}
	NoRemove CLSID
	{
		ForceRemove {3C406C5E-E3B1-11D2-8117-00E09801FDBE} = s 'Random Algorithm'
		{
			ProgID = s 'LoadBalancingAlgorithms.Random.1'
			VersionIndependentProgID = s 'LoadBalancingAlgorithms.Random'
			InprocServer32 = s '%MODULE%'
			{
				val ThreadingModel = s 'Free'
			}
            'Implemented Categories'
            {
                {9FDC5DE1-E180-11d2-B72C-00A0CC212296}
                {
                }
            }
			'TypeLib' = s '{3C406C51-E3B1-11D2-8117-00E09801FDBE}'
		}
	}
}
   |  0   R E G I S T R Y   џџg       0	        HKCR
{
	LoadBalancingAlgorithms.RoundRobin.1 = s 'RoundRobin Algorithm'
	{
		CLSID = s '{86AADFB2-E612-11D2-B72D-00A0CC212296}'
	}
	LoadBalancingAlgorithms.RoundRobin = s 'RoundRobin Algorithm'
	{
		CLSID = s '{86AADFB2-E612-11D2-B72D-00A0CC212296}'
		CurVer = s 'LoadBalancingAlgorithms.RoundRobin.1'
	}
	NoRemove CLSID
	{
		ForceRemove {86AADFB2-E612-11D2-B72D-00A0CC212296} = s 'RoundRobin Algorithm'
		{
			ProgID = s 'LoadBalancingAlgorithms.RoundRobin.1'
			VersionIndependentProgID = s 'LoadBalancingAlgorithms.RoundRobin'
			ForceRemove 'Programmable'
			InprocServer32 = s '%MODULE%'
			{
				val ThreadingModel = s 'Free'
			}
            'Implemented Categories'
            {
                {9FDC5DE1-E180-11d2-B72C-00A0CC212296}
                {
                }
            }
			'TypeLib' = s '{3C406C51-E3B1-11D2-8117-00E09801FDBE}'
		}
	}
}
a  0   R E G I S T R Y   џџh       0	        HKCR
{
	LoadBalancingAlgorithms.MethodTiming.1 = s 'MethodTiming Class'
	{
		CLSID = s '{86AADFB9-E612-11D2-B72D-00A0CC212296}'
	}
	LoadBalancingAlgorithms.MethodTiming = s 'MethodTiming Class'
	{
		CLSID = s '{86AADFB9-E612-11D2-B72D-00A0CC212296}'
		CurVer = s 'LoadBalancingAlgorithms.MethodTiming.1'
	}
	NoRemove CLSID
	{
		ForceRemove {86AADFB9-E612-11D2-B72D-00A0CC212296} = s 'MethodTiming Class'
		{
			ProgID = s 'LoadBalancingAlgorithms.MethodTiming.1'
			VersionIndependentProgID = s 'LoadBalancingAlgorithms.MethodTiming'
			InprocServer32 = s '%MODULE%'
			{
				val ThreadingModel = s 'Free'
			}
            'Implemented Categories'
            {
                {9FDC5DE1-E180-11d2-B72C-00A0CC212296}
                {
                }
            }
			'TypeLib' = s '{3C406C51-E3B1-11D2-8117-00E09801FDBE}'
		}
	}
}
     0   R E G I S T R Y   џџi       0	        HKCR
{
	LoadBalancingAlgorithms.CPULoad.1 = s 'CPULoad Class'
	{
		CLSID = s '{DD135284-E924-11D2-B72F-00A0CC212296}'
	}
	LoadBalancingAlgorithms.CPULoad = s 'CPULoad Class'
	{
		CLSID = s '{DD135284-E924-11D2-B72F-00A0CC212296}'
		CurVer = s 'LoadBalancingAlgorithms.CPULoad.1'
	}
	NoRemove CLSID
	{
		ForceRemove {DD135284-E924-11D2-B72F-00A0CC212296} = s 'CPULoad Class'
		{
			ProgID = s 'LoadBalancingAlgorithms.CPULoad.1'
			VersionIndependentProgID = s 'LoadBalancingAlgorithms.CPULoad'
			InprocServer32 = s '%MODULE%'
			{
				val ThreadingModel = s 'Free'
			}
			'TypeLib' = s '{3C406C51-E3B1-11D2-8117-00E09801FDBE}'
		}
	}
}
   ,   T Y P E L I B   џџ     0 	        MSFT      	      A                                   џџџџ          џџџџ       d   Ш   ,    є  \  X  џџџџ   д  $   џџџџ   ј     џџџџ   T     џџџџ   Д     џџџџ   4     џџџџ        џџџџ     H  џџџџ   \	  t   џџџџ   а	  8   џџџџ   џџџџ    џџџџ   
  T   џџџџ   \
  $   џџџџ   џџџџ    џџџџ   џџџџ    џџџџ   %"  
                                     `      (       ,           џџџџ                  џџџџ#" 
                                    x       <       џџџџ        џџџџ              џџџџ#" Ь
                                    Р       А       џџџџ        џџџџ              џџџџ%"                                      и            <           џџџџ                  џџџџ%"                                      №            P           џџџџ      @           џџџџ%"                                           4      d           џџџџ      `           џџџџЈ   и   џџџџџџџџџџџџџџџџџџџџџџџџx   џџџџ№   џџџџџџџџџџџџџџџџџџџџџџџџџџџџР   џџџџџџџџџџџџ    џџџџ  `   џџџџџџџџџџџџџџџџџџџџ0   Ql@<Був р§ОўџџџџџџџeКwо|QбЂк  јw<щџџџџџџџџcКwо|QбЂк  јw<щџџџџџџџџdКwо|QбЂк  јw<щџџџџџџџџ^l@<Був р§О       P7tБув р§Оd   џџџџ0     Р      F   џџџџ        Р      F   џџџџ жEcмцвЗ-  Ь!"Ш      ВпЊцвЗ-  Ь!",  џџџџЙпЊцвЗ-  Ь!"  џџџџRн$щвЗ/  Ь!"є  H   d      џџџџ   Ш       џџџџџџџџd      џџџџ0   Ш       џџџџџџџџd      џџџџP   Ш       џџџџџџџџd      џџџџp   Ш       џџџџџџџџ      Ј                                 - stdole2.tlbWWWџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџи   џџџџ4  џџџџџџџџџџџџџџџџ   џџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџ(   џџџџџџџџџџџџџџџџ  џџџџџџџџџџџџџџџџџџџџџџџџџџџџА   џџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџ|   џџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџь   џџџџ<   џџџџџџџџ    џџџџ`     џџџџџџџџџџџџџџџџФ   џџџџџџџџџџџџ    џџџџџџџџџџџџџџџџџџџџ pRLOADBALANCINGALGORITHMSLibWW    џџџџ8(єRandomWWd   џџџџ8э_ILoadBalancingAlgorithmWd   џџџџ rЧCreateInstanceWWџџџџџџџџ илrclsidWWџџџџџџџџ 3riidџџџџџџџџ ќФppvWШ   џџџџ8Е;IHostsWWШ   џџџџ ј?SetHostsџџџџџџџџ нnCountWWџџџџџџџџ
 kДrgwszHostsWW,  џџџџ
8­бRoundRobinWW  џџџџ8ѓЩMethodTimingє  џџџџ8CPULoadW( LoadBalancingAlgorithms 1.0 Type LibraryWW Random ClassWW RoundRobin ClassWW MethodTiming Class CPULoad ClassW џ    џ     џ    џ     @   ў     ў ўџ >   Created by MIDL version 8.00.0603 at Wed May 20 07:47:15 2020
 ФХ^WW [ WW       џџџџ0   D       H   L      <   <          	        |               (            ``       0   0         \ 	      и      0   ь        `Ф       N       џџ џџ     0	                 L o a d B a l a n c i n g A l g o r i t h m s                         