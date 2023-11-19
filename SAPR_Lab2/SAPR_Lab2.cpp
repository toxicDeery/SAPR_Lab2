#include <uf.h> //файл описаний общих функций
#include <uf_curve.h> //файл описаний функций кривых
#include <uf_csys.h> //файл описаний функций работы с координатами
#include <uf_mtx.h> //файл описаний функций работы с матрицами
void ufusr(char* param, int* retcode, int paramLen)
{
	// данные для окружности
	tag_t arc_id, wcs_tag; //тэги окружности
	 //и мировой системы координат
	UF_CURVE_arc_t arc_coords; //структура свойств дуги
	// объявление данных для матрицы поворота
	//зададим угол 60° и пересчитаем его в радианы
	double ugol_Y = 0;
	// объявим вектора осей Х и У
	double vec_X[3] = { 1, 0, 0 }, vec_Y[3] = { 0, 1, 0 };
	//объявим матрицы поворотов:
	double mtxP[9], //вокруг оси Х
		mtyP[9], //вокруг оси У
		mt[9]; //суммарную матрицу поворота
		//объявим теги систем координат
	tag_t teg_wcs, csys_id;
	// объявим точку начала координат
	double center[3] = { 0,0,0 };
	//если активизация функций Open API не прошла - прервать программу
	if (UF_initialize()) return;
	// начало кода построения окружности
	arc_coords.start_angle = 0.0; //начальный угол окружности
	arc_coords.end_angle = 360.0 * DEGRA; //конечный угол
	arc_coords.arc_center[0] = 0.0; //координата центра Х
	arc_coords.arc_center[1] = 0.0; //координата центра Y
	arc_coords.arc_center[2] = 0.0; //координата центра Z
	arc_coords.radius = 30.0; //радиус окружности
	for (int i = 0; i <= 4; i++) {
		// начало кода работы с матрицами
		// получим матрицу поворота на 60 вокруг оси Х
		UF_MTX3_rotate_about_axis(vec_X, ugol_Y, mtxP);
		// создадим тег суммарной матрицы поворота
		UF_CSYS_create_matrix(mtxP, &teg_wcs);
		// создадим тег системы координат на базе полученной матрицы
		UF_CSYS_create_csys(center, teg_wcs, &csys_id);
		// установим на экране созданную рабочую систему координат
		UF_CSYS_set_wcs(csys_id);
		UF_CSYS_ask_wcs(&wcs_tag); //получение абсолютных координат
		//"перенос" абсолютных координат на создаваемую окружность
		UF_CSYS_ask_matrix_of_object(wcs_tag, &arc_coords.matrix_tag);
		//построение окружности
		UF_CURVE_create_arc(&arc_coords, &arc_id);
		ugol_Y += 45 * DEGRA;
	}
	UF_terminate();
}
int ufusr_ask_unload(void) //функция выхода из приложения
{
	return (UF_UNLOAD_IMMEDIATELY);
}
