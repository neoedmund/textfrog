
FT_EXPORT int FT_Init_FreeType ( FT_Library * alibrary ) ;
FT_EXPORT int FT_New_Face ( void * library ,
	const char * filepathname ,
	FT_Long face_index ,
	FT_Face * aface ) ;
FT_EXPORT void FT_Library_Version ( void * library ,
	FT_Int * amajor ,
	FT_Int * aminor ,
	FT_Int * apatch ) ;
FT_EXPORT FT_ULong FT_Get_First_Char ( void * face ,
	FT_UInt * agindex ) ;
FT_EXPORT FT_ULong FT_Get_Next_Char ( void * face ,
	FT_ULong char_code ,
	FT_UInt * agindex ) ;
FT_EXPORT int FT_Load_Char ( void * face ,
	FT_ULong char_code ,
	FT_Int32 load_flags ) ;
FT_EXPORT int FT_Set_Char_Size ( void * face ,
	long /*  FT_F26Dot6 */ char_width ,
	long /*  FT_F26Dot6 */ char_height ,
	int horz_resolution ,
	int vert_resolution ) ;

