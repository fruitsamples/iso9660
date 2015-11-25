/*	File:		HighSierra.h		Description:Provide type and constant definitions relating to High Sierra 				format CDs.					Author:			Copyright: 	Copyright: � 1987-1999 by Apple Computer, Inc.				all rights reserved.		Disclaimer:	You may incorporate this sample code into your applications without				restriction, though the sample code has been provided "AS IS" and the				responsibility for its operation is 100% yours.  However, what you are				not permitted to do is to redistribute the source as "DSC Sample Code"				after having made changes. If you're going to re-distribute the source,				we require that you make it clear in the source that the code was				descended from Apple Sample Code, but that you've made changes.		Change History (most recent first):				6/24/99	Updated for Metrowerks Codewarror Pro 2.1(KG)*/#define	CDBLKSIZE	2048#define	HSVOLSTART	16		/* where we expect a Primary Volume Descriptor */#define HSTERMSTART	17		/* where we expect the Volume Descriptor Terminator */#define StdVolType	1		/* Primary Volume Descriptor type */#define	VolEndType	255		/* Volume Descriptor Set Terminator type */ /* * File Flags for Directory Records */#define existenceBit	0x01#define directoryBit	0x02#define associatedBit	0x04#define recordBit		0x08#define protectionBit	0x10#define multiextentBit	0x80/****************************************************************************//*	Exported Types															*//****************************************************************************/typedef unsigned char byte;/****************************************************************************//*	We need to ensure that these structures are aligned properly			*//****************************************************************************/#if defined(powerc) || defined (__powerc)#pragma options align=mac68k#endif#ifdef HIGHSIERRA/****************************************************************************//*	High Sierra (May 26, 1986) Standard										*//****************************************************************************//*  * Primary Volume Descriptor (PVD) */typedef struct{	long	lsbLogicalBlockNumber;	long	msbLogicalBlockNumber;	byte	VDType;					/* Must be 1 for PVD */	char	VSStdId[5];				/* Must be "CDROM" */	byte	VSStdVersion;			/* Must be 1 */	byte	Reserved1;				/* Must be 0's */	char	systemIdentifier[32];	char	volumeIdentifier[32];	char	Reserved2[8];			/* Must be 0's */	long	lsbVolumeSpaceSize;	long	msbVolumeSpaceSize;	char	Reserved3[32];			/* Must be 0's */	short	lsbVolumeSetSize;	short	msbVolumeSetSize;	short	lsbVolumeSetSequenceNumber;	short	msbVolumeSetSequenceNumber;	short	lsbLogicalBlockSize;	short	msbLogicalBlockSize;	long	lsbPathTableSize;	long	pathTableSize;	long	lsbPathTable1;			/* mandatory occurrence */	long	lsbPathTable2;			/* optional occurrence */	long	lsbPathTable3;			/* optional occurrence */	long	lsbPathTable4;			/* optional occurrence */	long	msbPathTable1;			/* mandatory occurrence */	long	msbPathTable2;			/* optional occurrence */	long	msbPathTable3;			/* optional occurrence */	long	msbPathTable4;			/* optional occurrence */	char	rootDirectoryRecord[34];	char	volumeSetIdentifier[128];	char	publisherIdentifier[128];	char	dataPreparerIdentifier[128];	char	applicationIdentifier[128];	char	copyrightFileIdentifier[32];	char	abstractFileIdentifier[32];	char	volumeCreation[16];	char	volumeModification[16];	char	volumeExpiration[16];	char	volumeEffective[16];	char	FileStructureStandardVersion;	char	Reserved4;				/* Must be 0's */	char	ApplicationUse[512];	char	FutureStandardization[680];} PVD, *PVDPtr;/* * Path Table */typedef char	dirIDArray[8];typedef struct{	long	dirLocation;	/* 1st logical block where directory is stored */	byte	XARlength;	/* Extended Attribute Record Length */	byte	len_di;			/* length of directory identifier */	short	parentDN;		/* parent directory number */	dirIDArray	dirID;		/* directory identifier: actual length is							 *	9 - [8+Len_di]; there is an extra blank							 *	byte if Len_di is odd.							 */} PathTableRecord, *PathTableRecordPtr;/* * Directory Record *	There exists one of these for each file in the directory. *	 */typedef struct{	char	macFlag[2];		/* $42 $41 - 'BA' famous value */	byte	systemUseID;	/* 06 = HFS */	byte	fileType[4];	/* such as 'TEXT' or 'STAK' */	byte	fileCreator[4];	/* such as 'hscd' or 'WILD' */	byte	finderFlags[2];} OldAppleExtension;typedef struct{	char	signature[2];		/* $41 $41 - 'AA' famous value */	byte	extensionLength;	/* $0E for this ID */	byte	systemUseID;	/* 02 = HFS */	byte	fileType[4];	/* such as 'TEXT' or 'STAK' */	byte	fileCreator[4];	/* such as 'hscd' or 'WILD' */	byte	finderFlags[2];} AppleExtension;typedef struct{	byte	len_dr;			/* directory record length */	byte	XARlength;	/* Extended Attribute Record Length */	long	lsbStart;	long	msbStart;			/* 1st logical block where file starts */	long	lsbDataLength;	long	msbDataLength;	byte	year;			/* since 1900 */	byte	month;	byte	day;	byte	hour;	byte	minute;	byte	second;	byte	fileFlags;	byte	reserved;		/* must be 0 */	byte	interleaveSize;	byte	interleaveSkip;	short	lsbVolSetSeqNum;	short	msbVolSetSeqNum;	/* which volume in volume set contains this file. */	byte	len_fi;				/* length of file identifier which follows */	char	fi[34];				/* file identifier: actual is 34-[33+Len_fi].									contains extra blank byte if Len_fi odd */	AppleExtension	apple;		/* this actually fits immediately after the fi[] */								/* field, or after its padding byte. */} DirRcd, *DirRcdPtr;	#endif/****************************************************************************//*	ISO 9660 (pANS Z39.86 198x) standard format								*//****************************************************************************//*  * Primary Volume Descriptor (PVD) */typedef struct{	byte	VDType;					/* Must be 1 for PVD */	char	VSStdId[5];				/* Must be "CD001" */	byte	VSStdVersion;			/* Must be 1 */	byte	Reserved1;				/* Must be 0's */	char	systemIdentifier[32];	char	volumeIdentifier[32];	char	Reserved2[8];			/* Must be 0's */	long	lsbVolumeSpaceSize;	long	msbVolumeSpaceSize;	char	Reserved3[32];			/* Must be 0's */	short	lsbVolumeSetSize;	short	msbVolumeSetSize;	short	lsbVolumeSetSequenceNumber;	short	msbVolumeSetSequenceNumber;	short	lsbLogicalBlockSize;	short	msbLogicalBlockSize;	long	lsbPathTableSize;	long	msbPathTableSize;	long	lsbPathTable1;			/* mandatory occurrence */	long	lsbPathTable2;			/* optional occurrence */	long	msbPathTable1;			/* mandatory occurrence */	long	msbPathTable2;			/* optional occurrence */	char	rootDirectoryRecord[34];	char	volumeSetIdentifier[128];	char	publisherIdentifier[128];	char	dataPreparerIdentifier[128];	char	applicationIdentifier[128];	char	copyrightFileIdentifier[37];	char	abstractFileIdentifier[37];	char	bibliographicFileIdentifier[37];	char	volumeCreation[17];	char	volumeModification[17];	char	volumeExpiration[17];	char	volumeEffective[17];	char	FileStructureStandardVersion;	char	Reserved4;				/* Must be 0's */	char	ApplicationUse[512];	char	FutureStandardization[653];} PVD, *PVDPtr;/* * Path Table */typedef char	dirIDArray[8];typedef struct{	byte	len_di;			/* length of directory identifier */	byte	XARlength;	/* Extended Attribute Record Length */	long	dirLocation;	/* 1st logical block where directory is stored */	short	parentDN;		/* parent directory number */	dirIDArray	dirID;		/* directory identifier: actual length is							 *	9 - [8+Len_di]; there is an extra blank							 *	byte if Len_di is odd.							 */} PathTableRecord, *PathTableRecordPtr;/* * Directory Record *	There exists one of these for each file in the directory. *	 */typedef struct{	char	macFlag[2];		/* $42 $41 - 'BA' famous value */	byte	systemUseID;	/* 06 = HFS */	byte	fileType[4];	/* such as 'TEXT' or 'STAK' */	byte	fileCreator[4];	/* such as 'hscd' or 'WILD' */	byte	finderFlags[2];} OldAppleExtension;typedef struct{	char	signature[2];		/* $41 $41 - 'AA' famous value */	byte	extensionLength;	/* $0E for this ID */	byte	systemUseID;	/* 02 = HFS */	byte	fileType[4];	/* such as 'TEXT' or 'STAK' */	byte	fileCreator[4];	/* such as 'hscd' or 'WILD' */	byte	finderFlags[2];} AppleExtension;typedef struct{	byte	len_dr;				/* directory record length */	byte	XARlength;			/* Extended Attribute Record Length */	long	lsbStart;	long	msbStart;			/* 1st logical block where file starts */	long	lsbDataLength;	long	msbDataLength;	byte	year;				/* since 1900 */	byte	month;	byte	day;	byte	hour;	byte	minute;	byte	second;	byte	gmtOffset;	byte	fileFlags;	byte	interleaveSize;	byte	interleaveSkip;	short	lsbVolSetSeqNum;	short	msbVolSetSeqNum;	/* which volume in volume set contains this file. */	byte	len_fi;				/* length of file identifier which follows */	char	fi[37];				/* file identifier: actual is 37-[36+Len_fi].									contains extra blank byte if Len_fi odd */	AppleExtension	apple;		/* this actually fits immediately after the fi[] */								/* field, or after its padding byte. */} DirRcd, *DirRcdPtr;	