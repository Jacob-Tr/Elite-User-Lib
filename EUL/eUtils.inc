#If defined EUTILS_INC
	#Endscript
#Endif

#If !defined EUTILS_INC_UTILITIES
	#tryinclude <EUL\Utils\eUtilities>
#Endif
#If !defined EUTILS_INC_COLORS
	#tryinclude <EUL\Utils\eColors>
#Endif
#If !defined EUTILS_INC_USERS
	#tryinclude <EUL\Utils\eUsers>
#Endif

#define EUTILS_INC

