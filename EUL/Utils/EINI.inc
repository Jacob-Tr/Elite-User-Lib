#if defined EUTILS_INC
	#endscript
#else
	#if defined EUTILS_INC_INI
		#endscript
	#endif
#endif
#define EUTILS_INC_INI

#tryinclude <EUL\Utils\eUtilities>
#if !defined EUTILS_INC_UTILITIES
	#error EINI Error: Unable to find eUtilities.
#endif

#define FILE_EXISTS(%0) fexist(%0)
#define FILE_OPEN(%0) OpenFile(%0)
#define FILE_OPENED if(temp_file_handle)

#define MAX_FILES 15
#define MAX_FILE_ADDR_SIZE 60
#define MAX_LINES 50
#define MAX_LINE_LEN 100

forward FileQueue(File:file_name[]);

new File:temp_file_handle, File:file_handle, get_char;
new bool:new_file = false, Timer:queue_timer;
new queued_files[MAX_FILES][MAX_FILE_ADDR_SIZE], file_queue = 0;
static file_info[MAX_FILES * MAX_LINES + 6][MAX_LINE_LEN];

bool:IsFileInQueue(File:file_name[])
{
	new file_name_str[MAX_FILE_ADDR_SIZE];
	strcat(file_name_str, file_name);
	
	for(new i = 0; i <= MAX_FILES; i++)
	{
		if(strcmp(file_name_str, queued_files[i], false) == 0) return true;
	}
	return false;
}

public FileQueue(File:file_name[])
{
	if(new_file)
	{
		if(!IsFileInQueue(file_name) queued_files[++file_queue] = file_name;
		new_file = false;
	}
		
	if(file_handle) return queue_timer = SetTimerEx("FileQueue", 250, 0, "%s", file_name);
	
	file_queue--;
	OpenFile(file_name);
	return;
}

GetInfoAddress(handleid, line) return ((handleid * MAX_LINES) + line);

GetHandleID(File:file_name[]) for(new i = 0; i <= MAX_FILES; i++) if(strcmp(queued_files[i], file_name) == 0) return i;
GetHandleIDFromInfoAddr(info_addr) return ((RoundDownToInt(info_addr / MAX_LINES));

MaxAddrSpace(handleid) return GetInfoAddress(handleid, MAX_LINES);

bool:IsLineWithinAddrSpace(handleid, line)
{
	new info_addr = GetInfoAddress(handleid, line);
	if(info_addr > MaxAddrSpace(handleid) || info_addr < (handleid * MAX_LINES)) return false;
	return true;
}

stock BuildFile(File:file_name[])
{
	if(!IsFileInQueue(file_name)) return;

	new line[MAX_LINE_LEN], current_line = 0, handleid = GetHandleID(file_name);
	new index = 0;
	new original_info_addr = GetInfoAddress(handleid, 0);

	file_handle = fopen(file_name);
	for( ; ; )
	{
	    new info_addr = original_info_addr + current_line; // Current line is no longer current(+1).
	    strcat(line, file_info[info_addr]);

	    if(!strlen(line) || !IsLineWithinAddrSpace(handleid, current_line))
		{
		    if(!IsLineWithinAddrSpace(handleid, current_line)) printf("EINI Error<%s>: File-space exceeded.", file_name);
		    CloseFile(file_handle);
			return;
		}

	    fseek(file_handle, index);
	    if(line[index] != EOS) fputchar(file_handle, line[index++], false);
	    else
	    {
	        fputchar(file_handle, '\n', false);

	        index = 0;
	        current_line++;
	        continue;
		}
	}

	CloseFile(file_handle);
	return;
}

stock AddInfo(File:file_name[], line, info[])
{
	if(!IsFileInQueue(file_name)) return;
	if(!strlen(info) || strlen(info) > MAX_LINE_LEN) return;
	const handleid = GetHandleID(file_name), info_addr = GetInfoAddress(handleid, line);
	
	format(file_info[info_addr], sizeof(file_info[info_addr]), "%d|%d %s", handleid, line, info);
	return;
}

stock RemoveInfo(File:file_name[], line)
{
    if(!IsFileInQueue(file_name)) return;
    
	strcat(file_info[info_addr], "");
	return;
}

stock OpenFile(const File:file_name[])
{
	if(strlen(file_name) > 60) return;
	if(!FILE_EXISTS(file_name)) return;
	if(file_queue == MAX_FILES && strlen(queued_files[0]) != 0)
	{
	    print("EINI Error: File queue overflow - Restarting server.");
	    SendRconCommand("gmx 0");
	    return;
	}
	else if(file_queue == MAX_FILES) file_queue = 0;
	
	if(IsFileInQueue(file_name))
	{
	    printf("File<%s>  is already in the queue.", file_name);
	    return;
	}
	if(file_handle) return SetTimerEx("FileQueue", 250, 0, "%s", file_name);
	
	strcat(queued_files[0], file_name);
	temp_file_handle = ftemp();
	
	file_handle = fopen(file_name, io_read);
	fseek(file_handle, 0, seek_start);
	
	new file_line = 1, line_index = 0, line_info[MAX_LINE_LEN], file_index = 0;
	const handleid = GetHandleID(file_name);
	
	while(get_char = fgetchar(file_handle, 0, false) != EOF)
	{
	    fseek(file_handle, file_index++, seek_start);
		get_char = fgetchar(file_handle, 0, false);
		
		build_line:
		if(get_char != '\n' && get_char != EOF)
		{
			line_info[line_index++] = get_char;
			goto build_line;
		}
		else if(getchar == '\n')
		{
			new info_addr = GetInfoAddress(handleid, file_line++);
			strcat(file_info[info_addr], line_info);
			line_index = 0;
		}
		else break;
	}
	fclose(file_handle);
	
	return;
}

stock CloseFile(File:file, handleid)
{
	if(!file_handle) return;
	new info_addr = GetInfoAddress(handleid, 0);
	new info_addr_max = MaxAddrSpace(handleid);
	
	for(new i = info_addr; i <= info_addr_max; i++) strcat(file_info[i], "");
	fclose(file);
}
	
	
	
	
	
















	
	
