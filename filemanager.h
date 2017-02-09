#pragma once

/*
	.xDD Format Explenation

	1) Image Width
	2) Image Height
	3) Extra Width
	4) Extra Height

	5) Number of Shape in Image
	6) Array of Info_t 
		
	First FileManager Load necessery information about Image'size (1), 2), 3), 4)) then Call Dimension which one build himself.
	When 5) is Read, FileManager Resize Main Contener and Copy there Info
	Finally DrawManager Building Shapes from Loaded Info
*/

class XPM	
{
	Array_t<Shapes*>* DrawnObj;
	char * RGB_HEX_CODE[16] = { "#000000", "#0000FF", "#008000", "#00FFFF", "#FF0000", "#FF00FF", "#A52A2A", "#D3D3D3", "#A9A9A9", "#ADD8E6", "#90EE90", "#E0FFFF", "#FFCCCB", "#ED5393", "#FFFF00", "#FFFFFF" };
	FILE* File;
	int Height, Width, perPixel, ColorsNumber, ColorsChar[16];
	char *Name;

	bool IsNotBlack(Vector2i_t toCheck)
	{
		for (auto It = DrawnObj->begin(); It != DrawnObj->rEnd(); It++)
		{
			if (((*It)->Intersect(toCheck)))
			{
				char s[2];
				_itoa((*It)->getColor(), s, 16);
				fprintf(File, s);
				return false;
			}
		}
		return true;
	}
	void SetHeader()
	{
		// Set !XPM
		fprintf(File, XPM_EXT);
		fprintf(File, "\n");

		//Set Width
		char Buff[3];
		_itoa(Width, Buff, 10);
		fprintf(File, Buff);
		fprintf(File, " ");

			//Set Height
		_itoa(Height, Buff, 10);
		fprintf(File, Buff);

		fprintf(File, XPM_COLORS_COUNT);
		fprintf(File, XPM_CHAR_PER_FILE);
		fprintf(File, "\n");

	}
	void SetColors()
	{
		for (int i = 0; i < 16; i++)
		{
			char s[2];
			_itoa(i, s, 16);
			fprintf(File, s);
			fprintf(File, " c ");
			fprintf(File, RGB_HEX_CODE[i]);
			fprintf(File, "\n");
		}
	}
	void SetPixel()
	{
		Vector2i_t toCheck = DEFAULT_CURSOR_POS;
		int i = 0;
		do
		{
				if(IsNotBlack(toCheck)==true)
				{
					char s[2];
					_itoa(0, s, 16);
					fprintf(File, s);
				}

				i++;

				if (i == Width)
				{
					fprintf(File, "\n");
					i = 0;
					toCheck.x = DEFAULT_CURSOR_POS.x;
					toCheck.y++;
				}	
			else
				toCheck.x++;

		} while (toCheck.y != Dimension_t::getEndPoint().y-1);

		fclose(File);
	}
	void CheckHeader()
	{
		char Head;
		char *Head1 = new char[6];

		int Width, Height, Char_per_file, Colors;
		fscanf(File, "%c", &Head);
		fscanf(File, "%s", Head1);
		fscanf(File, "%d", &Width);
		fscanf(File, "%d", &Height);
		fscanf(File, "%d", &Colors);
		fscanf(File, "%d", &Char_per_file);

		this->Width = Width;
		this->Height = Height;
		this->ColorsNumber = Colors;
		this->perPixel = Char_per_file;

		delete[] Head1;
	}

	void CheckColors()
	{
		char c;
		char* v = new char[8];
		for (int i = 0; i < 16; i++)
		{
			fscanf(File, "%x", &ColorsChar[i]);
			fscanf(File,"%c", &c);
			fscanf(File, "%c", &c);
			fscanf(File, "%c", &c);
			fscanf(File,"%s", v);
		}
		delete[] v;
	}

	void CheckPixels()
	{
		Vector2i_t toCheck = DEFAULT_CURSOR_POS;
		int i = 0, j = 0;
		Vector2i_t* Pos = new Vector2i_t[Width*Height];
		int * ColorTable = new int[Width*Height];
		char Map, *c;

		fscanf(File, "%c", &Map);
		do
		{ 
			fscanf(File,"%c", &Map);
			ColorTable[j] = strtoul(&Map, &c, 16);  //atoi(&Map[i]);
			Pos[j] = toCheck;

			j++;	//Table Index
			i++;	//Control Line, if<Width then it's time to change y

			if (i == Width)
			{
				fscanf(File, "%c", &Map);
				i = 0;
				toCheck.x = DEFAULT_CURSOR_POS.x;
				toCheck.y++;
			}
			else
				toCheck.x++;

		} while (toCheck.y != Dimension_t::getEndPoint().y - 1);

		
		for (int i = 0; i < DrawnObj->Length(); i++)
		{
			delete *DrawnObj->end();
			DrawnObj->Erase();
		}
		DrawnObj->Add(new Pasted_t(Pos, ColorTable, Width*Height));

		delete[] Pos, ColorTable;
		fclose(File);
	}
public:
	XPM(char* Name,int Width, int Height, Array_t<Shapes*>* DrawnObj):
		Width(Width),
		Height(Height),
		DrawnObj(DrawnObj),
		Name(Name)
	{}

	void Save()
	{
		File = fopen(Name, "wt");

		SetHeader();
		SetColors();
		SetPixel();
	}

	void Load()
	{
		File = fopen(Name, "r");
		CheckHeader();
		BasicInfo_t::ImageWidth = Width;
		BasicInfo_t::ImageHeight = Height;
		Dimension_t::setImageDimension();
		CheckColors();
		CheckPixels();
	}

};

class FileManager //TODO Own *.XD extension BMP XPM2	
{
	static char* FileName;
	static int FileLength;

	static bool hasExtension(char* Name, int NameLength, char* Ext, int ExtLength) //TODO Flexible extension
	{
		for (int i = 0; i < ExtLength; i++)
			if (Name[NameLength - i - 1] != Ext[ExtLength - i])		
				return false;
		return true;
	}
	static bool hasExtension(char* Name, int NameLength)
	{
		return hasExtension(Name, NameLength, OWN_EXTENSION, EXTENSION_SIZE);

	}
	static void addExtension(char* UserName, int NameLength)
	{
		char* Name = new char[NameLength];
		memset(Name, 0, NameLength);
		strcat(Name, UserName);
		strcat(Name, OWN_EXTENSION);
		setFileName(Name);
		delete[] Name;
	}

public:
	static Array_t<char*> FileMarks;
	static void setFileName(char* FileName)
	{
		if (FileManager::FileName != nullptr)
			delete[] FileManager::FileName;

		FileManager::FileLength = strlen(FileName) + 1;
		FileManager::FileName = new char[FileManager::getFileLength()];
		memcpy(FileManager::FileName, FileName, FileLength * sizeof(char));
	}
	static char* getFileName()
	{
		return FileName;
	}
	static int getFileLength()
	{
		return FileLength;
	}
	template<class typ>
	static Rectangle* CreateNewFile(Array_t<typ>* DrawnObjs)
	{
		FILE* File;

		if (hasExtension(FileName, FileLength) == false)
			addExtension(FileName, FileLength + EXTENSION_SIZE);

		Rectangle *ImageDimension = Dimension_t::setImageDimension();

		for (int i = 0; i < DrawnObjs->Length(); i++)
		{
			delete *DrawnObjs->end();
			DrawnObjs->Erase();
		}

		try
		{
			File = fopen(getFileName(), "wb");
			if (File == nullptr)
				throw 0;
		}
		catch (...)
		{
			setFileName("Cannot Create New File");
			return nullptr;
		}

		fclose(File);

		return ImageDimension;
	}

	static char* InputText(const char* text)
	{
		int KeyCode;
		char Buffer[255];
		int Length = 0;
		gotoxy(INPUT_NFO_POS);
		textcolor(DARKGRAY);
		cputs(text);
		memset(Buffer, 0, 255);
		gotoxy(INPUT_BOX_POS);
		do
		{
			textbackground(WHITE);

			KeyCode = getch();
			putch(KeyCode);

			if (KeyCode == ENTER)
			{
				if (Length == 0)
					return NULL;

				break;
			}
			if (KeyCode == ESCAPE)
				return NULL;

			Buffer[Length] = KeyCode;
			Length++;

		} while (KeyCode != ENTER);

		char* UserName = new char[Length + 1];
		memset(UserName, 0, Length);
		strncat(UserName, Buffer, Length);

		textbackground(BLACK);
		textcolor(BLACK);

		gotoxy(INPUT_NFO_POS);

		for (int i = 0; i <= Length + 40; i++) ///Czysci Linie Wpisywania
			putch(' ');

		textcolor(DARKGRAY);
		return UserName;
	}
	template<class typ>
	static void Save(Array_t<typ>* DrawnObjs)
	{
		FILE* File;
		int Size = DrawnObjs->Length();

		if (hasExtension(FileName, FileLength,".xpm",4) == true)
		{
			XPM obj(FileManager::getFileName(), BasicInfo_t::ImageWidth, BasicInfo_t::ImageHeight, DrawnObjs);
			obj.Save();
			return;
		}

		if (hasExtension(FileName, FileLength) == false)
			addExtension(FileName, FileLength + EXTENSION_SIZE);

		try
		{
			File = fopen(getFileName(), "wb");

			if (File == nullptr)
				throw 0;
		}
		catch (int)
		{
			setFileName("Cannot Save File");
			return;
		}

		fwrite(&BasicInfo_t::ImageWidth, sizeof(int), 1, File);
		fwrite(&BasicInfo_t::ImageHeight, sizeof(int), 1, File);
		fwrite(&BasicInfo_t::ExtraWidth, sizeof(int), 1, File);
		fwrite(&BasicInfo_t::ExtraHeight, sizeof(int), 1, File);

		fwrite(&Size, sizeof(int), 1, File);

		Info_t *tab = new Info_t[Size];

		int i = 0;

		for (Shapes** objtodraw = DrawnObjs->begin(); objtodraw != DrawnObjs->rEnd(); objtodraw++)
		{
			tab[i] = ((*objtodraw)->getInfo());
			i++;
		}

		fwrite(tab, sizeof(Info_t), Size, File);
		fclose(File);
		delete[] tab;
	}

	template<class typ>
	static Rectangle* Read(Array_t<typ>* DrawnObjs)
	{
		Info_t *ReadInfo = nullptr;
		int Size = NULL;
		FILE* File;

		if (hasExtension(FileName, FileLength, ".xpm", 4) == true)
		{
			XPM obj(FileManager::getFileName(), BasicInfo_t::ImageWidth, BasicInfo_t::ImageHeight, DrawnObjs);
			obj.Load();
			return Dimension_t::getImageDimension();
		}

		if (hasExtension(FileName, FileLength) == false)
			addExtension(FileName, FileLength + EXTENSION_SIZE);

		try
		{
			File = fopen(FileManager::getFileName(), "rb");

			if (File == nullptr)
				throw 0;
		}
		catch (...)
		{
			setFileName("File Not Exist");
			return nullptr;
		}

		fread(&BasicInfo_t::ImageWidth, sizeof(int), 1, File);
		fread(&BasicInfo_t::ImageHeight, sizeof(int), 1, File);
		fread(&BasicInfo_t::ExtraWidth, sizeof(int), 1, File);
		fread(&BasicInfo_t::ExtraHeight, sizeof(int), 1, File);
		fread(&Size, sizeof(int), 1, File);

		try
		{
			ReadInfo = new Info_t[Size];
		}
		catch (...)
		{
			setFileName("Wrong Number of Elements");
			return nullptr;
		}

		fread(ReadInfo, sizeof(Info_t), Size, File);
		fclose(File);

		for (int i = 0; i < DrawnObjs->Length(); i++)
		{
			delete *DrawnObjs->end();
			DrawnObjs->Erase();
		}

		for (int i = 0; i < Size; i++)
			switch (ReadInfo[i].getInfo().Type)
			{
			case 'R':
					DrawnObjs->Add(new Rectangle);
					break;

			case 'L':
					DrawnObjs->Add(new Line);
					break;

			case 'P':
				DrawnObjs->Add(new Pasted_t);
				break;

			default:
				DrawnObjs->Add(new Pasted_t);
				break;
			}
		for (int i = 0; i < Size; i++)
			(*(DrawnObjs->begin() + i))->BuildFromInfo(ReadInfo[i]);

		delete[] ReadInfo;
		return Dimension_t::setImageDimension();
	}
};

// Set Static Variable From FileManager
int FileManager::FileLength = 0;
char* FileManager::FileName = nullptr;
Array_t<char*> FileManager::FileMarks;