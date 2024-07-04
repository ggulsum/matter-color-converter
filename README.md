# RGB'den XYZ ve xyY Renk Alanı Dönüşümü

 RGB renk uzayından xyY renk uzayına dönüşüm yapmamızın amacı, renkleri insan gözünün algıladığı şekilde ifade etmektir. RGB (Kırmızı, Yeşil, Mavi) renk uzayı, elektronik cihazlarda kullanılan bir renk modelidir ve doğrudan insan gözünün renk algılamasıyla örtüşmez. Diğer yandan, xyY renk uzayı, renklerin parlaklık ve renk bileşenlerinin ayrı olarak temsil edildiği bir modeldir. Bu dönüşüm, renk doğruluğunu artırmak ve renkler arasında daha doğru bir karşılaştırma yapabilmek için önemlidir.


### Ana Fonksiyonlar

- **`gamma_correction`:** Belirli bir renk değerine gamma correction uygular.
- **`inv_gamma_correction`:** Belirli bir renk değerine ters gamma correction uygular.
- **`matrix_times_array`:** Renk alanı dönüşümleri yapmak için bir matrisi bir dizi ile çarpar.
- **`rgbToXYZ`:** Bir RGB rengini XYZ renk alanına dönüştürür.
- **`xyzToXyY`:** Bir XYZ rengini xyY renk alanına dönüştürür.
- **`xyYToXYZ`:** Bir xyY rengini XYZ renk alanına dönüştürür.
- **`xyzToRGB`:** Bir XYZ rengini tekrar RGB renk alanına dönüştürür.
- **`round_color`:** RGB renk değerlerini en yakın tam sayıya yuvarlar.

### Kaynak 
https://babelcolor.com/index_htm_files/A%20review%20of%20RGB%20color%20spaces.pdf

### Programda Elde Edilen Değerleri Test Etme
https://viereck.ch/hue-xy-rgb/


![image](https://github.com/ggulsum/matter-color-converter/assets/129232751/1e60fed6-6abb-4f2e-8488-4156ec6b5bed)

