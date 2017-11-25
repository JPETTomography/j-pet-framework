How to use JPetReader:

1. Create JPetReader instance. It will correspond to one file of your choice,
   which name you can already pass in constructor.

2. If you haven't yet opened the file in constructor. Use:
	OpenFile(const char* file_name);
   method to do so.

3. File is internally divided into sections. Now you have to provide this section
   name:
	 ReadData(const char* objname);

4. In order to get get number of objects stored in the file, use:
	GetEntries();
   method, so you can determine the range for your loops.

5. To access an object, you have to do two things:
	a) use 
		GetEntry(int entryNo);
	   method to set reader's internal pointer to specyfic object.
	   It also returns the size of object that the pointer is set to,
	   so you can determine whether it is even there, or it is the 
	   object you want.
	b) use
		GetData();
	   method, which will return the object, on which you set pointer
	   in point a). This method returns a reference to a TNamed object.
	   Most likely you will want to cast it to a specyfic data type,
	   that you know is there.

6. When your work is done, use:
	CloseFile();
   method, to make your JPetReader clean everything inside him.
   After that you can proceed with all the fun and open another file with it!