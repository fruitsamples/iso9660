/*	File:		support.c		Description:	Author:			Copyright: 	Copyright: � 1999 by Apple Computer, Inc.				all rights reserved.		Disclaimer:	You may incorporate this sample code into your applications without				restriction, though the sample code has been provided "AS IS" and the				responsibility for its operation is 100% yours.  However, what you are				not permitted to do is to redistribute the source as "DSC Sample Code"				after having made changes. If you're going to re-distribute the source,				we require that you make it clear in the source that the code was				descended from Apple Sample Code, but that you've made changes.		Change History (most recent first):				6/24/99	Updated for Metrowerks Codewarror Pro 2.1(KG)*/#include <stdio.h>#include <ctype.h>#include <string.h>#include <Types.h>#include <QuickDraw.h>#include <Packages.h>#include <StandardFile.h>#include "support.h"typedef	unsigned char	byte;/************************************************************************ * *  Function:		pStrCopy * *  Purpose:		copy a pascal string from p1 to p2 * *  Returns:		nothing * *  Side Effects:	p2 gets filled with contents of p1 * *  Description:	simple loop, copying from p1 to p2 for length *					determined by first byte of p1. * ************************************************************************/voidpStrCopy(StringPtr p1, StringPtr p2){	register short len;		len = *p2++ = *p1++;	while (--len>=0)		*p2++=*p1++;}/************************************************************************ * *  Function:		pStrLen * *  Purpose:		return length of pascal string * *  Returns:		short * *  Side Effects:	none * *  Description:	The first byte of a pascal string contains the *					length of the string.  Return that value. * ************************************************************************/shortpStrLen(StringPtr p){	return (p[0]);}/************************************************************************ * *  Function:		CreateISOName * *  Purpose:		Create ISO name from pstring. * *  Returns:		nothing * *  Side Effects:	dest is filled. * *  Description:	An ISO file name is 31 characters plus '.;1', all *					in uppercase.  Copy and convert file name, with *					any bogus characters converted to underscore '_'. *					If there was no period in the file name, *					add one.  Add ";1" to the end of the file name. * ************************************************************************/shortCreateISOName(char *dest, StringPtr src){	short	i;	short	limit;	short	nameSize;	Boolean	madeDot;			limit = pStrLen(src);		dest[0] = toupper(src[1]);		if (dest[0] == '\000' || dest[0] == '\001')		return 1;	/* don't add version stuff to myself or parent */	for (i = 1; i < limit; i++)		dest[i] = (isalnum(src[i+1])) ? toupper(src[i+1]) : '_';		madeDot = false;	for (i = limit; i > 0 && madeDot == false; i--)		if (dest[i] == '_')		{			dest[i] = '.';			madeDot = true;		}	nameSize = limit;		if (madeDot == false)		/* we don't have a period. Add one */		dest[nameSize++] = '.';	dest[nameSize++] = ';';	dest[nameSize++] = '1';		/* version number */	return nameSize;}/************************************************************************ * *  Function:		HFSFile * *  Purpose:		get the name and vRefNum of an HFS File * *  Returns:		Boolean *						true	a file was selected *						false	no file. Please stop * *  Side Effects:	*fn and *vRefNum get filled in * *  Description:	Call SFGetFile to get the file to be operated upon. * ************************************************************************/BooleanHFSFile(StringPtr fn, short *vRefNum){	Point	SFGwhere;	SFReply	reply;		SFGwhere.v = 90;	SFGwhere.h = 82;	SFGetFile(SFGwhere, (StringPtr)"\pChoose File to Add to ISO disk", 0L, -1, 0L, 0L, &reply );	if (reply.good) {		pStrCopy( reply.fName, fn );		*vRefNum = reply.vRefNum;		return(true);	}	else return(false);}/************************************************************************ * *  Function:		ClearOut * *  Purpose:		set memory to zeros * *  Returns:		nothing * *  Side Effects:	*buffer is zeroed out * *  Description:	zero out buffer for count bytes. * ************************************************************************/voidClearOut(Ptr buffer, short count){	short	i;		for (i = 0; i < count; i++)		buffer[i] = 0;}/************************************************************************ * *  Function:		SpaceOut * *  Purpose:		set memory to spaces * *  Returns:		nothing * *  Side Effects:	*buffer is spaced out * *  Description:	Put spaces into buffer for count bytes. * ************************************************************************/voidSpaceOut(Ptr buffer, short count){	short	i;		for (i = 0; i < count; i++)		buffer[i] = ' ';}/************************************************************************ * *  Function:		CharCopy * *  Purpose:		copy and fill with blanks * *  Returns:		nothing * *  Side Effects:	*dest is filled with contents of src & blanks * *  Description:	copy from *src to *dest for the length specified. *					src is assumed to point to a C null-delimited string. *					If src is smaller than length in size, dest is filled *					with blanks. * ************************************************************************/voidCharCopy(char *dest, char *src, short length){	short 	i;	short	j;		i = 0;	while (*dest++ = *src++)		i++;		*dest--;	i--;	/* so that no null terminator is left over */		if (i < length)		for (j = i; j < length; j++)			*dest++ = ' ';}/************************************************************************ * *  Function:	NormalizeLong * *  Purpose:	normalize a long number that's in lsb format * *  Returns:	long * *  Side Effects:	none * *  Description: *				takes a long in lsb format order and converts it *				to msb format order.  For example, the long value *				0x12345678 becomes 0x78563412 *				0x78563412 becomes 0x12345678 * * ************************************************************************/longNormalizeLong(long incoming){	byte	*byteArray;	long	result;		byteArray = (byte *) &incoming;	result = (long) byteArray[0] | 			 (long) byteArray[1] << 8 | 			 (long) byteArray[2] << 16 |			 (long) byteArray[3] << 24;		return result;}/************************************************************************ * *  Function:	NormalizeWord * *  Purpose:	normalize a word number that's in lsb format * *  Returns:	word * *  Side Effects:	none * *  Description: *				takes a word in lsb format order and converts it *				to msb format order.  For example, the word value *				0x1234 becomes 0x3412 *				0x3412 becomes 0x1234 * * ************************************************************************/shortNormalizeWord(short incoming){	byte	*byteArray;	short	result;		byteArray = (byte *) &incoming;	result = (short) byteArray[0] | 			 (short) byteArray[1] << 8;		return result;}/************************************************************************ * *  Function:	NormalizeVolumeName * *  Purpose:	convert a string to conform to ISO 9660 naming standards * *  Returns:	none * *  Side Effects:	changes the string "someString" * *  Description: *				ISO 9660 forces volume names to be only alphanumeric *				characters plus underscore.  This routine converts a *				string of arbitrary length to such a volume name string, *				converting all illegal characters to underscore. * * ************************************************************************/voidNormalizeVolumeName(char *someString){	short	i;		for (i = 0; i < strlen(someString); i++)		someString[i] = (isalnum(someString[i])) ? toupper(someString[i]) : '_';}/************************************************************************ * *  Function:		GetFileInfo * *  Purpose:		get lengths of file rsrc and data forks * *  Returns:		OSErr *						noErr, unless PBHGetVInfo has an error. * *  Side Effects:	dataLength & rsrcLength are changed * *  Description:	 call PBGetFInfo() and return its results. * ************************************************************************/OSErrGetFileInfo(StringPtr name, short vRefNum, long *rsrcLength, long *dataLength, OSType *fType, OSType *fCreator, short *flags){	HParamBlockRec	io;	OSErr			result;		io.fileParam.ioCompletion = 0L;	io.fileParam.ioNamePtr = name;	io.fileParam.ioVRefNum = vRefNum;	io.fileParam.ioFVersNum = 0;	io.fileParam.ioFDirIndex = 0;	result = PBGetFInfo((ParmBlkPtr)&io, false);	if (result == noErr)	{		*rsrcLength = io.fileParam.ioFlRLgLen;		*dataLength = io.fileParam.ioFlLgLen;		*fType = io.fileParam.ioFlFndrInfo.fdType;		*fCreator = io.fileParam.ioFlFndrInfo.fdCreator;		*flags = io.fileParam.ioFlFndrInfo.fdFlags;	}	else	{		*rsrcLength = 0L;		*dataLength = 0L;		*fType = 0L;		*fCreator = 0L;		*flags = 0;	}	return result;}/************************************************************************ * *  Function:		GetFinderFlags * *  Purpose:		get finder flags for a file * *  Returns:		OSErr *						noErr, unless PBGetFInfo has an error. * *  Side Effects:	flags value is changed * *  Description:	 call PBGetFInfo() and return its results. * ************************************************************************/OSErrGetFinderFlags(StringPtr name, short vRefNum, short *flags){	HParamBlockRec	io;	OSErr			result;		io.fileParam.ioCompletion = 0L;	io.fileParam.ioNamePtr = name;	io.fileParam.ioVRefNum = vRefNum;	io.fileParam.ioFVersNum = 0;	io.fileParam.ioFDirIndex = 0;	result = PBGetFInfo((ParmBlkPtr)&io, false);	if (result == noErr)		*flags = io.fileParam.ioFlFndrInfo.fdFlags;	else		*flags = 0;	return result;}