#include <stdio.h>

/* ========================================================= */
/*                                                           */
/*   Archivo : pv_yield_estimator_Espanol.c                  */
/*   Proyecto: Herramienta de Planificacion Fotovoltaica     */
/*                                                           */
/*   Desarrollado por: Oscar Matallana                       */
/*                                                           */
/*   Descripcion:                                            */
/*   Herramienta educativa de planificacion y                */
/*   estimacion de rendimiento fotovoltaico usando           */
/*   supuestos de ingenieria realistas y lenguaje C          */
/*   amigable para principiantes.                            */
/*                                                           */
/* ========================================================= */

#define QUICK_MODE 1
#define ADVANCED_MODE 2

typedef struct s_result
{
	float	roof_area;
	float	irradiation;
	float	pr;
	float	installed_power;
	float	adjusted_yield;
	float	yearly_savings;
}	t_result;

void	clear_input_buffer(void)
{
	char	c;

	while ((c = getchar()) != '\n' && c != EOF)
		;
}

int	get_valid_int(int min, int max, char *message)
{
	int	value;
	int	valid;

	valid = 0;

	while (valid == 0)
	{
		printf("%s", message);

		if (scanf("%d", &value) != 1)
		{
			printf("Error: Solo numeros.\n\n");
			clear_input_buffer();
		}
		else if (value < min || value > max)
		{
			printf("Error: El valor debe estar entre ");
			printf("%d y %d.\n\n", min, max);
			clear_input_buffer();
		}
		else
		{
			clear_input_buffer();
			valid = 1;
		}
	}
	return (value);
}

float	get_valid_float(float min,
			float max,
			char *message)
{
	float	value;
	int		valid;

	valid = 0;

	while (valid == 0)
	{
		printf("%s", message);

		if (scanf("%f", &value) != 1)
		{
			printf("Error: Solo numeros.\n\n");
			clear_input_buffer();
		}
		else if (value < min || value > max)
		{
			printf("Error: El valor debe estar entre ");
			printf("%.2f y %.2f.\n\n",
				min, max);
			clear_input_buffer();
		}
		else
		{
			clear_input_buffer();
			valid = 1;
		}
	}
	return (value);
}

void	print_header(void)
{
	printf("==================================================\n");
	printf("========== ESTIMADOR DE RENDIMIENTO FV ===========\n");
	printf("==================================================\n\n");

	printf("Desarrollado por Oscar Matallana\n");
	printf("Herramienta de Planificacion FV\n\n");

	printf("Software educativo de ingenieria fotovoltaica\n");
	printf("para planificacion y estimacion de energia solar.\n\n");

	printf("IMPORTANTE:\n");
	printf("- Usa punto decimal para numeros decimales\n");
	printf("- Ejemplo: 0.85\n\n");
}

void	print_mode_information(void)
{
	printf("==================================================\n");
	printf("=============== MODOS DE CALCULO =================\n");
	printf("==================================================\n\n");

	printf("1. ESTIMACION RAPIDA\n");
	printf("- Estimacion fotovoltaica rapida\n");
	printf("- Duracion aproximada: 1-2 minutos\n\n");

	printf("2. ESTIMACION AVANZADA DE INGENIERIA\n");
	printf("- Simulacion de ingenieria detallada\n");
	printf("- Incluye orientacion y sombreado\n");
	printf("- Duracion aproximada: 4-7 minutos\n\n");
}

void	print_region_menu(void)
{
	printf("\n==================================================\n");
	printf("=============== SELECCIONAR REGION ================\n");
	printf("==================================================\n\n");

	printf("1. America del Norte\n");
	printf("2. America del Sur\n");
	printf("3. Europa\n");
	printf("4. Africa\n");
	printf("5. Asia\n");
	printf("6. Oceania\n\n");
}

void	print_region_cities(int region)
{
	if (region == 1)
	{
		printf("\n============== AMERICA DEL NORTE =================\n\n");

		printf("1. Toronto, Canada -> 1200 kWh/m2/ano\n");
		printf("2. Vancouver, Canada -> 1100 kWh/m2/ano\n");
		printf("3. Montreal, Canada -> 1150 kWh/m2/ano\n");

		printf("4. Phoenix, USA -> 2300 kWh/m2/ano\n");
		printf("5. Los Angeles, USA -> 1900 kWh/m2/ano\n");
		printf("6. Nueva York, USA -> 1400 kWh/m2/ano\n");

		printf("7. Ciudad de Mexico, Mexico -> 1900 kWh/m2/ano\n");
		printf("8. Monterrey, Mexico -> 2100 kWh/m2/ano\n");
		printf("9. Guadalajara, Mexico -> 2000 kWh/m2/ano\n\n");
	}
	else if (region == 2)
	{
		printf("\n============== AMERICA DEL SUR ===================\n\n");

		printf("1. Bogota, Colombia -> 1450 kWh/m2/ano\n");
		printf("2. Cartagena, Colombia -> 1950 kWh/m2/ano\n");
		printf("3. Medellin, Colombia -> 1550 kWh/m2/ano\n");
		printf("4. Cali, Colombia -> 1650 kWh/m2/ano\n");

		printf("5. Sao Paulo, Brasil -> 1700 kWh/m2/ano\n");
		printf("6. Rio de Janeiro, Brasil -> 1800 kWh/m2/ano\n");
		printf("7. Salvador, Brasil -> 2000 kWh/m2/ano\n");

		printf("8. Buenos Aires, Argentina -> 1600 kWh/m2/ano\n");
		printf("9. Cordoba, Argentina -> 1800 kWh/m2/ano\n");
		printf("10. Mendoza, Argentina -> 2100 kWh/m2/ano\n\n");
	}
	else if (region == 3)
	{
		printf("\n================== EUROPA ========================\n\n");

		printf("1. Berlin, Alemania -> 1100 kWh/m2/ano\n");
		printf("2. Munich, Alemania -> 1190 kWh/m2/ano\n");
		printf("3. Hamburgo, Alemania -> 1050 kWh/m2/ano\n");

		printf("4. Madrid, Espana -> 1900 kWh/m2/ano\n");
		printf("5. Sevilla, Espana -> 2100 kWh/m2/ano\n");
		printf("6. Barcelona, Espana -> 1750 kWh/m2/ano\n");

		printf("7. Estocolmo, Suecia -> 1000 kWh/m2/ano\n");
		printf("8. Gotemburgo, Suecia -> 980 kWh/m2/ano\n");
		printf("9. Malmo, Suecia -> 1050 kWh/m2/ano\n\n");
	}
	else if (region == 4)
	{
		printf("\n================== AFRICA ========================\n\n");

		printf("1. Casablanca, Marruecos -> 2000 kWh/m2/ano\n");
		printf("2. Marrakesh, Marruecos -> 2200 kWh/m2/ano\n");
		printf("3. Rabat, Marruecos -> 1900 kWh/m2/ano\n");

		printf("4. Lagos, Nigeria -> 1800 kWh/m2/ano\n");
		printf("5. Abuya, Nigeria -> 2000 kWh/m2/ano\n");
		printf("6. Kano, Nigeria -> 2200 kWh/m2/ano\n");

		printf("7. Ciudad del Cabo, Sudafrica -> 2100 kWh/m2/ano\n");
		printf("8. Johannesburgo, Sudafrica -> 2200 kWh/m2/ano\n");
		printf("9. Durban, Sudafrica -> 1800 kWh/m2/ano\n\n");
	}
	else if (region == 5)
	{
		printf("\n==================== ASIA =======================\n\n");

		printf("1. Riad, Arabia Saudita -> 2400 kWh/m2/ano\n");
		printf("2. Jeddah, Arabia Saudita -> 2300 kWh/m2/ano\n");
		printf("3. Dammam, Arabia Saudita -> 2350 kWh/m2/ano\n");

		printf("4. Tokio, Japon -> 1450 kWh/m2/ano\n");
		printf("5. Osaka, Japon -> 1500 kWh/m2/ano\n");
		printf("6. Sapporo, Japon -> 1200 kWh/m2/ano\n");

		printf("7. Pekin, China -> 1700 kWh/m2/ano\n");
		printf("8. Shanghai, China -> 1400 kWh/m2/ano\n");
		printf("9. Shenzhen, China -> 1500 kWh/m2/ano\n");

		printf("10. Bangkok, Tailandia -> 1800 kWh/m2/ano\n");
		printf("11. Seul, Corea del Sur -> 1350 kWh/m2/ano\n");
		printf("12. Taipei, Taiwan -> 1600 kWh/m2/ano\n");

		printf("13. Manila, Filipinas -> 1900 kWh/m2/ano\n");
		printf("14. Yakarta, Indonesia -> 1700 kWh/m2/ano\n");
		printf("15. Nueva Delhi, India -> 2100 kWh/m2/ano\n\n");
	}
	else if (region == 6)
	{
		printf("\n================== OCEANIA ======================\n\n");

		printf("1. Sidney, Australia -> 1800 kWh/m2/ano\n");
		printf("2. Perth, Australia -> 2200 kWh/m2/ano\n");
		printf("3. Melbourne, Australia -> 1700 kWh/m2/ano\n");

		printf("4. Auckland, Nueva Zelanda -> 1400 kWh/m2/ano\n");
		printf("5. Wellington, Nueva Zelanda -> 1350 kWh/m2/ano\n");
		printf("6. Christchurch, Nueva Zelanda -> 1450 kWh/m2/ano\n\n");
	}
}

int	get_city_limit(int region)
{
	if (region == 1)
		return (9);
	else if (region == 2)
		return (10);
	else if (region == 3)
		return (9);
	else if (region == 4)
		return (9);
	else if (region == 5)
		return (15);
	else if (region == 6)
		return (6);
	return (0);
}

float	get_city_irradiation(int region, int city)
{
	if (region == 1)
	{
		float values[9] = {
			1200, 1100, 1150,
			2300, 1900, 1400,
			1900, 2100, 2000};

		return (values[city - 1]);
	}
	else if (region == 2)
	{
		float values[10] = {
			1450, 1950, 1550, 1650,
			1700, 1800, 2000,
			1600, 1800, 2100};

		return (values[city - 1]);
	}
	else if (region == 3)
	{
		float values[9] = {
			1100, 1190, 1050,
			1900, 2100, 1750,
			1000, 980, 1050};

		return (values[city - 1]);
	}
	else if (region == 4)
	{
		float values[9] = {
			2000, 2200, 1900,
			1800, 2000, 2200,
			2100, 2200, 1800};

		return (values[city - 1]);
	}
	else if (region == 5)
	{
		float values[15] = {
			2400, 2300, 2350,
			1450, 1500, 1200,
			1700, 1400, 1500,
			1800, 1350, 1600,
			1900, 1700, 2100};

		return (values[city - 1]);
	}
	else if (region == 6)
	{
		float values[6] = {
			1800, 2200, 1700,
			1400, 1350, 1450};

		return (values[city - 1]);
	}
	return (0);
}

float	select_irradiation_value(void)
{
	int		menu;
	int		region;
	int		city;
	int		city_limit;
	float	irradiation;

	printf("\n==================================================\n");
	printf("========== MENU DE IRRADIANCIA SOLAR =============\n");
	printf("==================================================\n\n");

	printf("1. Preajustes rapidos por region\n");
	printf("2. Ingresar valor de irradiancia personalizado\n\n");

	menu = get_valid_int(1, 2, "Opcion: ");

	if (menu == 2)
	{
		irradiation = get_valid_float(
				500,
				3000,
				"Irradiancia solar (kWh/m2/ano): ");
		return (irradiation);
	}

	print_region_menu();

	region = get_valid_int(1, 6, "Region: ");

	print_region_cities(region);

	city_limit = get_city_limit(region);

	city = get_valid_int(1, city_limit, "Ciudad: ");

	irradiation = get_city_irradiation(region, city);

	return (irradiation);
}

void	print_electricity_examples(void)
{
	printf("\n==================================================\n");
	printf("PRECIOS DE ELECTRICIDAD RESIDENCIAL EJEMPLO\n");
	printf("==================================================\n\n");

	printf("Alemania: 0.30 - 0.45 EUR/kWh\n");
	printf("USA:      0.12 - 0.25 USD/kWh\n");
	printf("China:    0.08 - 0.15 CNY/kWh\n\n");

	printf("Rango realista tipico residencial:\n");
	printf("0.05 - 0.60 moneda/kWh\n\n");
}

float	get_orientation_factor(void)
{
	int		option;
	float	factor;

	printf("\n==================================================\n");
	printf("============== ORIENTACION DEL TECHO =============\n");
	printf("==================================================\n\n");

	printf("1. Orientado al Sur\n");
	printf("2. Sureste / Suroeste\n");
	printf("3. Este / Oeste\n");
	printf("4. Orientado al Norte\n\n");

	option = get_valid_int(1, 4, "Opcion: ");

	factor = 1.0;

	if (option == 1)
		factor = 1.00;
	else if (option == 2)
		factor = 0.95;
	else if (option == 3)
		factor = 0.85;
	else if (option == 4)
		factor = 0.65;

	return (factor);
}

float	get_shading_factor(void)
{
	int		option;
	float	factor;

	printf("\n==================================================\n");
	printf("================= NIVEL DE SOMBREADO ============\n");
	printf("==================================================\n\n");

	printf("1. Sin sombreado\n");
	printf("2. Sombreado leve\n");
	printf("3. Sombreado moderado\n");
	printf("4. Sombreado fuerte\n\n");

	option = get_valid_int(1, 4, "Opcion: ");

	factor = 1.0;

	if (option == 1)
		factor = 1.00;
	else if (option == 2)
		factor = 0.90;
	else if (option == 3)
		factor = 0.75;
	else if (option == 4)
		factor = 0.50;

	return (factor);
}

void	print_results(t_result result)
{
	printf("\n==================================================\n");
	printf("==================== RESULTADOS ==================\n");
	printf("==================================================\n\n");

	printf("Capacidad FV Instalada:\n");
	printf("%.2f kWp\n\n", result.installed_power);

	printf("Rendimiento Energetico Anual Ajustado:\n");
	printf("%.0f kWh/ano\n\n", result.adjusted_yield);

	printf("Ahorro de Electricidad Anual Estimado:\n");
	printf("%.2f moneda/ano\n\n",
		result.yearly_savings);
}

void	print_comparison_table(t_result first,
				t_result second)
{
	printf("\n==================================================\n");
	printf("========== COMPARACION DE UBICACIONES ============\n");
	printf("==================================================\n\n");

	printf("%-25s %-15s %-15s\n",
		"Parametro",
		"Ubicacion 1",
		"Ubicacion 2");

	printf("--------------------------------------------------\n");

	printf("%-25s %-15.2f %-15.2f\n",
		"Area del Techo (m2)",
		first.roof_area,
		second.roof_area);

	printf("%-25s %-15.0f %-15.0f\n",
		"Irradiancia",
		first.irradiation,
		second.irradiation);

	printf("%-25s %-15.2f %-15.2f\n",
		"Relacion de Rendimiento",
		first.pr,
		second.pr);

	printf("%-25s %-15.2f %-15.2f\n",
		"Potencia Instalada",
		first.installed_power,
		second.installed_power);

	printf("%-25s %-15.0f %-15.0f\n",
		"Rendimiento Ajustado",
		first.adjusted_yield,
		second.adjusted_yield);

	printf("%-25s %-15.2f %-15.2f\n",
		"Ahorro Anual",
		first.yearly_savings,
		second.yearly_savings);

	printf("\n");
}

int	ask_repeat_program(void)
{
	int	option;

	printf("\n==================================================\n");
	printf("=============== SIGUIENTE ACCION =================\n");
	printf("==================================================\n\n");

	printf("1. Nuevo calculo\n");
	printf("2. Salir\n\n");

	option = get_valid_int(1, 2, "Opcion: ");

	return (option);
}

int	ask_comparison(void)
{
	int	option;

	printf("\n==================================================\n");
	printf("================ MODO COMPARACION ================\n");
	printf("==================================================\n\n");

	printf("Deseas comparar con otra ubicacion?\n\n");

	printf("1. Si\n");
	printf("2. No\n\n");

	option = get_valid_int(1, 2, "Opcion: ");

	return (option);
}

t_result	run_quick_mode(void)
{
	t_result	result;
	float		electricity_price;

	printf("\n==================================================\n");
	printf("================ ESTIMACION RAPIDA ===============\n");
	printf("==================================================\n\n");

	result.roof_area = get_valid_float(
			1,
			1000,
			"Area de techo utilizable (m2): ");

	result.irradiation = select_irradiation_value();

	print_electricity_examples();

	electricity_price = get_valid_float(
			0.05,
			0.60,
			"Precio de electricidad (moneda/kWh): ");

	printf("\n==================================================\n");
	printf("========== RELACION DE RENDIMIENTO (PR) ==========\n");
	printf("==================================================\n\n");

	printf("0.95 -> sistema optimizado excepcionalmente\n");
	printf("0.90 -> instalacion moderna muy buena\n");
	printf("0.85 -> sistema residencial realista bueno\n");
	printf("0.80 -> sistema promedio\n");
	printf("0.75 -> perdidas notables\n\n");

	result.pr = get_valid_float(
			0.75,
			0.95,
			"Relacion de Rendimiento - PR (0.75 - 0.95): ");

	result.installed_power = result.roof_area * 0.22;

	result.adjusted_yield =
		result.roof_area
		* result.irradiation
		* 0.22
		* result.pr;

	result.yearly_savings =
		result.adjusted_yield
		* electricity_price;

	print_results(result);

	return (result);
}

t_result	run_advanced_mode(void)
{
	t_result	result;

	float	module_power;
	float	module_length;
	float	module_width;
	float	module_area;
	float	module_power_density;

	float	electricity_price;
	float	orientation_factor;
	float	shading_factor;

	printf("\n==================================================\n");
	printf("========== MODO AVANZADO DE INGENIERIA ===========\n");
	printf("==================================================\n\n");

	module_power = get_valid_float(
			100,
			800,
			"Potencia nominal del modulo (Wp): ");

	module_length = get_valid_float(
			0.5,
			3.0,
			"Largo del modulo (m): ");

	module_width = get_valid_float(
			0.5,
			2.0,
			"Ancho del modulo (m): ");

	result.roof_area = get_valid_float(
			1,
			1000,
			"Area de techo utilizable (m2): ");

	result.irradiation = select_irradiation_value();

	print_electricity_examples();

	electricity_price = get_valid_float(
			0.05,
			0.60,
			"Precio de electricidad (moneda/kWh): ");

	printf("\n==================================================\n");
	printf("========== RELACION DE RENDIMIENTO (PR) ==========\n");
	printf("==================================================\n\n");

	printf("0.95 -> sistema optimizado excepcionalmente\n");
	printf("0.90 -> instalacion moderna muy buena\n");
	printf("0.85 -> sistema residencial realista bueno\n");
	printf("0.80 -> sistema promedio\n");
	printf("0.75 -> perdidas notables\n\n");

	result.pr = get_valid_float(
			0.75,
			0.95,
			"Relacion de Rendimiento - PR (0.75 - 0.95): ");

	orientation_factor = get_orientation_factor();

	shading_factor = get_shading_factor();

	module_area = module_length * module_width;

	module_power_density =
		(module_power / 1000)
		/ module_area;

	result.installed_power =
		result.roof_area
		* module_power_density;

	result.adjusted_yield =
		result.roof_area
		* result.irradiation
		* module_power_density
		* result.pr
		* orientation_factor
		* shading_factor;

	result.yearly_savings =
		result.adjusted_yield
		* electricity_price;

	print_results(result);

	return (result);
}

int	main(void)
{
	int			mode;
	int			restart;
	int			comparison;

	t_result	first;
	t_result	second;

	restart = 1;

	while (restart == 1)
	{
		print_header();

		print_mode_information();

		mode = get_valid_int(
				1,
				2,
				"Selecciona modo: ");

		if (mode == QUICK_MODE)
			first = run_quick_mode();
		else
			first = run_advanced_mode();

		comparison = ask_comparison();

		if (comparison == 1)
		{
			printf("\nCALCULO DE SEGUNDA UBICACION\n");

			if (mode == QUICK_MODE)
				second = run_quick_mode();
			else
				second = run_advanced_mode();

			print_comparison_table(first,
					second);
		}

		restart = ask_repeat_program();

		printf("\n");
	}

	printf("==================================================\n");
	printf("Gracias por usar Estimador de Rendimiento FV.\n");
	printf("==================================================\n");

	return (0);
}