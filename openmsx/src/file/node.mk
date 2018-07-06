# $Id: node.mk 12468 2012-04-10 21:36:14Z manuelbi $

include build/node-start.mk

SRC_HDR:= \
	File \
	FileContext \
	Filename \
	FileBase \
	LocalFile \
	FileOperations \
	CompressedFileAdapter \
	GZFileAdapter \
	ZipFileAdapter \
	ZlibInflate \
	ReadDir \
	FilePool \
	PreCacheFile \
	LocalFileReference

HDR_ONLY:= \
	FileException \
	FileNotFoundException

include build/node-end.mk

