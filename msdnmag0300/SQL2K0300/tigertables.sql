use tiger

DECLARE @tb varchar(12)

set @tb='TGR42101'

EXEC('CREATE TABLE [' + @tb + '02' + '] (
	[rt] [char] (1) NULL ,
	[version] [int] NULL ,
	[tlid] [int] NULL ,
	[rtsq] [int] NULL ,
	[long1] [int] NULL ,
	[lat1] [int] NULL ,
	[long2] [int] NULL ,
	[lat2] [int] NULL ,
	[long3] [int] NULL ,
	[lat3] [int] NULL ,
	[long4] [int] NULL ,
	[lat4] [int] NULL ,
	[long5] [int] NULL ,
	[lat5] [int] NULL ,
	[long6] [int] NULL ,
	[lat6] [int] NULL ,
	[long7] [int] NULL ,
	[lat7] [int] NULL ,
	[long8] [int] NULL ,
	[lat8] [int] NULL ,
	[long9] [int] NULL ,
	[lat9] [int] NULL ,
	[long10] [int] NULL ,
	[lat10] [int] NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '01' + '] (
	[rt] [char] (10) NULL ,
	[version] [int] NULL ,
	[tlid] [int] NULL ,
	[side1] [int] NULL ,
	[source] [varchar] (1) NULL ,
	[fedirp] [varchar] (2) NULL ,
	[fename] [varchar] (30) NULL ,
	[fetype] [varchar] (4) NULL ,
	[fedirs] [varchar] (2) NULL ,
	[cfcc] [varchar] (3) NULL ,
	[fraddl] [varchar] (50) NULL ,
	[toaddl] [varchar] (50) NULL ,
	[fraddr] [varchar] (50) NULL ,
	[toaddr] [varchar] (50) NULL ,
	[friaddl] [int] NULL ,
	[toiaddl] [int] NULL ,
	[friaddr] [int] NULL ,
	[toiaddr] [int] NULL ,
	[zipl] [int] NULL ,
	[zipr] [int] NULL ,
	[fairl] [int] NULL ,
	[fairr] [int] NULL ,
	[trustl] [char] (1) NULL ,
	[trustr] [char] (1) NULL ,
	[bbspcen] [char] (1) NULL ,
	[bbsppart] [char] (1) NULL ,
	[statel] [int] NULL ,
	[stater] [int] NULL ,
	[countyl] [int] NULL ,
	[countyr] [int] NULL ,
	[fmcdl] [int] NULL ,
	[fmcdr] [int] NULL ,
	[fsmcdl] [int] NULL ,
	[fsmcdr] [int] NULL ,
	[fpll] [int] NULL ,
	[fplr] [int] NULL ,
	[ctbna90l] [int] NULL ,
	[ctbna90r] [int] NULL ,
	[blk90l] [varchar] (4) NULL ,
	[blk90r] [varchar] (4) NULL ,
	[frlong] [int] NULL ,
	[frlat] [int] NULL ,
	[tolong] [int] NULL ,
	[tolat] [int] NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '03' + '] (
	[rt] [char] (1) NOT NULL ,
	[version] [int] NOT NULL ,
	[tlid] [int] NOT NULL ,
	[state90l] [int] NULL ,
	[state90r] [int] NULL ,
	[coun90l] [int] NULL ,
	[coun90r] [int] NULL ,
	[fmcd90l] [int] NULL ,
	[fmcd90r] [int] NULL ,
	[fpl90l] [int] NULL ,
	[fpl90r] [int] NULL ,
	[ctbna90l] [int] NULL ,
	[ctbna90r] [int] NULL ,
	[rs1] [char] (3) NULL ,
	[rs2] [char] (3) NULL ,
	[rs3] [char] (3) NULL ,
	[rs4] [char] (3) NULL ,
	[blk90l] [char] (4) NULL ,
	[blk90r] [char] (4) NULL ,
	[airl] [int] NULL ,
	[airr] [int] NULL ,
	[rs5] [char] (3) NULL ,
	[rs6] [char] (3) NULL ,
	[anrcl] [int] NULL ,
	[anrcr] [int] NULL ,
	[rs7] [char] (4) NULL ,
	[rs8] [char] (4) NULL ,
	[vtdl] [char] (4) NULL ,
	[vtdr] [char] (4) NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '04' + '] (
	[rt] [char] (1) NULL ,
	[version] [int] NULL ,
	[tlid] [int] NULL ,
	[rtsq] [int] NULL ,
	[feat1] [int] NULL ,
	[feat2] [int] NULL ,
	[feat3] [int] NULL ,
	[feat4] [int] NULL ,
	[feat5] [int] NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '05' + '] (
	[rt] [char] (1) NULL ,
	[state] [int] NULL ,
	[county] [int] NULL ,
	[feat] [int] NULL ,
	[feadirp] [char] (2) NULL ,
	[fename] [char] (30) NULL ,
	[fetype] [char] (4) NULL ,
	[fedirs] [char] (2) NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '06' + '] (
	[rt] [char] (1) NULL ,
	[version] [int] NULL ,
	[tlid] [int] NULL ,
	[rtsq] [int] NULL ,
	[fraddl] [char] (11) NULL ,
	[toaddl] [char] (11) NULL ,
	[fraddr] [char] (11) NULL ,
	[toaddr] [char] (11) NULL ,
	[friaddl] [int] NULL ,
	[toiaddl] [int] NULL ,
	[friaddr] [int] NULL ,
	[toiaddr] [int] NULL ,
	[zipl] [int] NULL ,
	[zipr] [int] NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '07' + '] (
	[rt] [char] (1) NULL ,
	[version] [int] NULL ,
	[state] [int] NULL ,
	[county] [int] NULL ,
	[land] [int] NULL ,
	[source] [char] (1) NULL ,
	[cfcc] [char] (3) NULL ,
	[laname] [varchar] (50) NULL ,
	[lalong] [int] NULL ,
	[lalat] [int] NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '08' + '] (
	[rt] [char] (1) NULL ,
	[version] [int] NULL ,
	[state] [int] NULL ,
	[county] [int] NULL ,
	[cenid] [int] NULL ,
	[polyid] [int] NULL ,
	[land] [char] (10) NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '09' + '] (
	[rt] [char] (1) NULL ,
	[version] [int] NULL ,
	[state] [int] NULL ,
	[county] [int] NULL ,
	[cenid] [int] NULL ,
	[polyid] [int] NULL ,
	[source] [char] (1) NULL ,
	[cfcc] [char] (3) NULL ,
	[kglname] [char] (30) NULL ,
	[kgladd] [char] (11) NULL ,
	[kglzip] [int] NULL ,
	[kglzip4] [int] NULL ,
	[feat] [int] NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '0A' + '] (
	[rt] [char] (1) NULL ,
	[version] [int] NULL ,
	[state] [int] NULL ,
	[county] [int] NULL ,
	[cenid] [int] NULL ,
	[polyid] [int] NULL ,
	[fair] [int] NULL ,
	[fmcd] [int] NULL ,
	[fpl] [int] NULL ,
	[ctbna90] [int] NULL ,
	[blk90] [char] (4) NULL ,
	[cd106] [int] NULL ,
	[cd108] [int] NULL ,
	[sdelm] [char] (5) NULL ,
	[sdmid] [char] (5) NULL ,
	[sdsec] [char] (5) NULL ,
	[sduni] [char] (5) NULL ,
	[taz] [char] (5) NULL ,
	[ua] [int] NULL ,
	[urbflag] [char] (1) NULL ,
	[ctpp] [char] (4) NULL ,
	[rs9] [char] (9) NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '0C' + '] (
	[rt] [char] (1) NULL ,
	[version] [int] NULL ,
	[state] [int] NULL ,
	[county] [int] NULL ,
	[fipsyr] [char] (2) NULL ,
	[fips] [int] NULL ,
	[fipscc] [char] (2) NULL ,
	[pdc] [char] (1) NULL ,
	[lasad] [int] NULL ,
	[anrc] [int] NULL ,
	[cmsamsa] [int] NULL ,
	[pmsa] [int] NULL ,
	[air] [int] NULL ,
	[vtd] [char] (6) NULL ,
	[ua] [int] NULL ,
	[name] [char] (66) NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '0H' + '] (
	[rt] [char] (1) NULL ,
	[version] [int] NULL ,
	[state] [int] NULL ,
	[county] [int] NULL ,
	[tlid] [int] NULL ,
	[hist] [char] (1) NULL ,
	[source] [char] (1) NULL ,
	[tlidfr1] [int] NULL ,
	[tlidfr2] [int] NULL ,
	[tlidto1] [int] NULL ,
	[tlidto2] [int] NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '0I' + '] (
	[rt] [char] (1) NULL ,
	[version] [int] NULL ,
	[tlid] [int] NULL ,
	[state] [int] NULL ,
	[county] [int] NULL ,
	[rtlink] [char] (1) NULL ,
	[cenidl] [int] NULL ,
	[polyidl] [int] NULL ,
	[cenidr] [int] NULL ,
	[polyidr] [int] NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '0P' + '] (
	[rt] [char] (1) NULL ,
	[version] [int] NULL ,
	[state] [int] NULL ,
	[county] [int] NULL ,
	[cenid] [int] NULL ,
	[polyid] [int] NULL ,
	[polylong] [int] NULL ,
	[polylat] [int] NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '0R' + '] (
	[rt] [char] (1) NULL ,
	[version] [char] (4) NULL ,
	[state] [char] (2) NULL ,
	[county] [char] (3) NULL ,
	[cenid] [char] (5) NULL ,
	[maxid] [char] (10) NULL ,
	[minid] [char] (10) NULL ,
	[highid] [char] (10) NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '0S' + '] (
	[rt] [char] (1) NULL ,
	[version] [int] NULL ,
	[state] [int] NULL ,
	[county] [int] NULL ,
	[cenid] [int] NULL ,
	[polyid] [int] NULL ,
	[water] [int] NULL ,
	[cmsamsa] [int] NULL ,
	[pmsa] [int] NULL ,
	[fair] [int] NULL ,
	[air] [int] NULL ,
	[trust] [char] (1) NULL ,
	[anrc] [int] NULL ,
	[statecu] [int] NULL ,
	[countycu] [int] NULL ,
	[fccity] [int] NULL ,
	[fmcd] [int] NULL ,
	[fsmcd] [int] NULL ,
	[fpl] [int] NULL ,
	[ctbna90] [int] NULL ,
	[blk90] [char] (4) NULL ,
	[rs10] [char] (1) NULL ,
	[cdcu] [int] NULL ,
	[stsenate] [char] (6) NULL ,
	[sthouse] [char] (6) NULL ,
	[vtd00] [char] (6) NULL ,
	[rs11] [char] (6) NULL ,
	[rs12] [char] (1) NULL ,
	[rs13] [char] (5) NULL ,
	[rd14] [char] (5) NULL 
) ON [PRIMARY]')

EXEC('CREATE TABLE [' + @tb + '0Z' + '] (
	[rt] [char] (1) NULL ,
	[version] [int] NULL ,
	[tlid] [int] NULL ,
	[rtsq] [int] NULL ,
	[zip4l] [int] NULL ,
	[zip4r] [int] NULL 
) ON [PRIMARY]')
