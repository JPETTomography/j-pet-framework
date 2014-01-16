How to use JPetReader:

1. Create JPetReader instance. It will correspond to one file of your choice,
   which name you can already pass in constructor.

2. If you haven't yet opened the file in constructor. Use:
	OpenFile(const char* file_name);
   method to do so.

3. In order to get get number of objects stored in the file, use:
	GetEntries();
   method, so you can determine the range for your loops.

4. To access an object, you have to do two things:
	a) use 
		GetEntry(int entryNo);
	   method to set reader's internal pointer to specyfic object.
	   It also returns the size of object that the pointer is set to,
	   so you can determine whether it is even there, or it is the 
	   object you want.
	b) use
		GetData();
	   method, which will return the object, on which you set pointer
	   in point a). This method returns a reference to a TNamed object,
	   which you most likely will want to cast to a specyfic data type,
	   that you know is there.

5. Optionally the file might be divided into some sections.
   In that case, to switch between them, you have to use:
	ReadData(const char* objname);
   where the argument is the name of particular section.
   After that you can proceed through steps 3 and 4.

6. When your work is done, use:
	CloseFile();
   method, to make your JPetReader clean everything inside him.
   After that you can proceed with all the fun and open another file with it!