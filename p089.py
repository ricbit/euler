import roman as Roman

decoder = {
  'I': 1,
  'V': 5,
  'X': 10,
  'L': 50,
  'C': 100,
  'D': 500,
  'M': 1000
}

roman_input = [x.strip() for x in open('p089_roman.txt', 'rt').readlines()]
roman_output = []

ans = 0
for original_roman in roman_input:
  roman = original_roman.replace("IV", "IIII")
  roman = roman.replace("IX", "VIIII")
  roman = roman.replace("XL", "XXXX")
  roman = roman.replace("XC", "LXXXX")
  roman = roman.replace("CD", "CCCC")
  roman = roman.replace("CM", "DCCCC")
  decode = sum(decoder[x] for x in roman.strip())
  recoded = Roman.toRoman(decode)
  ans += len(original_roman) - len(recoded)
print(ans)
  
