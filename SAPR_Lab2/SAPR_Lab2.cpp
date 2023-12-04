#include <stdio.h>
#include <uf.h> 
#include <uf_modl.h> 

void ufusr(char* param, int* retcode, int paramLen) {
	// определим создание нового самостоятельного тела 
	UF_FEATURE_SIGN sign = UF_NULLSIGN;
	//это тело должно начинаться в заданных координатах Х, У, Z 
	double cyl_orig[3] = { -50.0, 0.0, 0.0 };
	double cyl_orig_1[3] = { 0.0, -50.0, 0.0 };
	double cyl_orig_2[3] = { 0.0, 0.0, -50.0 };
	char height[125] = "100"; //высоту цилиндра зададим в 70 мм 
	char diam[125] = "50"; //диаметр-в 50 мм 
	//и орты направления главной диагонали координат будут по 1 
	double direction[3] = { 0.0, 1.0, 0.0 };
	double direction1[3] = { 1.0, 0.0, 0.0 };
	double direction2[3] = { 0.0, 0.0, 1.0 };
	tag_t cyl_obj; //определим переменную для будущего тега цилиндра
	if (!UF_initialize()) {
		//выполним построение цилиндра 
		UF_MODL_create_cyl1(sign, cyl_orig, height, diam, direction1, &cyl_obj);
		UF_MODL_create_cyl1(sign, cyl_orig_1, height, diam, direction, &cyl_obj);
		UF_MODL_create_cyl1(sign, cyl_orig_2, height, diam, direction2, &cyl_obj);
		UF_terminate();
	}
} //типовая функция завершения приложения
int ufusr_ask_unload(void) {
	return (UF_UNLOAD_IMMEDIATELY);
}
