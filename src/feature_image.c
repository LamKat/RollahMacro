/*
 * Demonstrate how to display a two color, black and white bitmap image with no
 * transparency.
 *
 * The original source image is from:
 *  <http://openclipart.org/detail/26728/aiga-litter-disposal-by-anonymous>
 *
 * The source image was converted from an SVG into a RGB bitmap using Inkscape.
 * It has no transparency and uses only black and white as colors.
 */

#include "pebble.h"
	
void strthing();

static Window *s_main_window;
static BitmapLayer *s_image_layer;
static GBitmap *s_image_bitmap;

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  s_image_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NO_LITTER);

  s_image_layer = bitmap_layer_create(bounds);
  bitmap_layer_set_bitmap(s_image_layer, s_image_bitmap);
  bitmap_layer_set_alignment(s_image_layer, GAlignCenter);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_image_layer));
}

static void main_window_unload(Window *window) {
  bitmap_layer_destroy(s_image_layer);
  gbitmap_destroy(s_image_bitmap);
}

static void init() {
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();	
	strthing();
  app_event_loop();
  deinit();
}














//##################################################



int16_t calculate(char *str);
int16_t fuiNextInt(char *szStr, int16_t *iLen);
void quickSort( int16_t a[], int16_t l, int16_t r);
int16_t partition( int16_t a[], int16_t l, int16_t r);
char *itoa(int16_t num);
void Prnt(int16_t *arriRolls, int16_t iMin, int16_t iMax);

void strthing(){
	char *szStr = "20d100";
	int32_t rtn = calculate(szStr);
	APP_LOG(APP_LOG_LEVEL_DEBUG,"Input = %s, Output = %d", szStr, (int) rtn);		
}

int16_t calculate(char *szStr){
	int16_t iLen,i,iMin=0,iMax=0;
	int16_t iRollCount = fuiNextInt(szStr, &iLen);
	szStr += iLen + 1;
	int16_t iSideCount = fuiNextInt(szStr, &iLen);
	szStr += iLen;
	APP_LOG(APP_LOG_LEVEL_DEBUG,"Rolls = %d, Sides = %d", iRollCount, iSideCount);
	int16_t arriRolls[iRollCount];
	iMax = iRollCount - 1;
	srand(time(NULL));
	for(i=0;i<iRollCount;i++){
		arriRolls[i] = (rand() % iSideCount) + 1;
		//APP_LOG(APP_LOG_LEVEL_DEBUG,"arriRoll[%d] = %d", i, arriRolls[i]);
	}
	quickSort(arriRolls,iMin,iMax);
	for(i=0;i<=iMax;i++){
		APP_LOG(APP_LOG_LEVEL_DEBUG,"arriRoll[%d] = %d", i, arriRolls[i]);
	}
	
	//Prnt(arriRolls,iMin,iMax);
	char operator;
	int16_t operand;
	int32_t iTemp;
	while(szStr[0] != '\0'){
		
		Prnt(arriRolls,iMin,iMax);
		operator = szStr[0];
		if (operator == 'H' || operator == 'h'){
			return arriRolls[iMax];
		}else if (operator == 'L' || operator == 'l'){			
			return arriRolls[iMin];
		}
		operand = fuiNextInt(++szStr, &iLen);
		szStr += iLen;
		if(operand == 0) operand ++;
		switch(operator){
			case 'd':
			case 'D':
				//iMax -= operand;
				iMax = iMin + --operand;
				break;
			case 'k':
			case 'K':
				//iMin += operand;
				iMin = iMax - --operand;
				break;
			case '<':
				iTemp = 0;
				for(i=iMin;i<=iMax;i++){
					if(arriRolls[i] < operand) iTemp++;
				}
				iMin = 0;
				iMax = 0;
				arriRolls[0] = iTemp;
				break;
			case '>':
				iTemp = 0;
				for(i=iMin;i<=iMax;i++){
					if(arriRolls[i] > operand) iTemp++;
				}
				iMin = 0;
				iMax = 0;
				arriRolls[0] = iTemp;
				break;
			case '-':
				operand = -operand;
			case '+':
				iTemp = 0;
				for(i=iMin;i<=iMax;i++){
					iTemp += arriRolls[i];
				}
				iMin = iMax = 0;
				arriRolls[0] = iTemp + operand;
				break;
		}
	}
	iTemp = 0;
	APP_LOG(APP_LOG_LEVEL_DEBUG,"Min = %d, Max = %d", iMin, iMax);
	for(i=iMin;i<=iMax;i++){
		iTemp += arriRolls[i];
		//APP_LOG(APP_LOG_LEVEL_DEBUG,"arriRoll[%d] = %d", i, arriRolls[i]);
	}
	Prnt(arriRolls,iMin,iMax);
	return iTemp;
}




void Prnt(int16_t *arriRolls, int16_t iMin, int16_t iMax){
	int i = iMin;
	char szFinal[30];
	strcpy(szFinal,"[");
	while (strlen(szFinal) < 25 && i < iMax){
		
		strcat(szFinal,itoa(arriRolls[i++]));
		strcat(szFinal,",");
	}
	if (i < iMax){
		
		strcat(szFinal,"..");
	}else{
		
		strcat(szFinal,itoa(arriRolls[i++]));
	}
		strcat(szFinal,"]");
	APP_LOG(APP_LOG_LEVEL_DEBUG,"num = %s",szFinal);
}


char *itoa(int16_t num)
{
	static char buff[20] = {};
	int i = 0, temp_num = num, length = 0;
	char *string = buff;
	if(num >= 0) {
		// count how many characters in the number
		while(temp_num) {
		temp_num /= 10;
		length++;
		}
		// assign the number to the buffer starting at the end of the 
		// number and going to the begining since we are doing the
		// integer to character conversion on the last number in the
		// sequence
		for(i = 0; i < length; i++) {
			buff[(length-1)-i] = '0' + (num % 10);
			num /= 10;
		}
			buff[i] = '\0'; // can't forget the null byte to properly end our string
	}
	return string;
}






int16_t fuiNextInt(char *szStr, int16_t *iLen){
	int16_t i,j;	
	for(i=0;szStr[i]>='0' && szStr[i]<='9';i++);
	
	char szTemp[i];
	for(j=0;j<i;j++){
		szTemp[j] = szStr[j]; 
	}
	szTemp[i] = '\0';
	*iLen = i;
	return atoi(szTemp);
}

void quickSort( int16_t a[], int16_t l, int16_t r){
   int16_t j;
   if( l < r ){
       j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }
}

int16_t partition( int16_t a[], int16_t l, int16_t r) {
   int16_t pivot, i, j, t;
   pivot = a[l];
   i = l; j = r+1;
   while(1){
   	do ++i; while( a[i] <= pivot && i <= r );
   	do --j; while( a[j] > pivot );
   	if( i >= j ) break;
   	t = a[i]; a[i] = a[j]; a[j] = t;
   }
   t = a[l]; a[l] = a[j]; a[j] = t;
   return j;
}
