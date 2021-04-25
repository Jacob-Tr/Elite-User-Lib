#If defined EUTILS_INC
	#Endscript
#Endif

#If !defined EUTILS_INC_UTILITIES
	#tryinclude <EUL\Utils\eUtilities>
#Endif
#If !defined EUTILS_INC_COLORS
	#tryinclude <EUL\Utils\eColors>
#Endif

#define EUTILS_INC

