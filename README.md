# germicide-fastdfs
The repository is a guide to how to use "germicide/fastdfs"(a docker image). See https://registry.hub.docker.com/r/germicide/fastdfs.The image provides pptx\docx\xlsx to pdf,mp4 to m3u8,etc.
To get the function of docx2pdf, you can send a post request with the parameter “type=pdf”,taking the binary data of the file in the http body.
To get the function of mp42m3u8, you can send a post request with the parameter “type=m3u8”,taking the binary data of the file in the http body.

