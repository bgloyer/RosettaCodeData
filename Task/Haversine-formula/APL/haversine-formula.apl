r←6371
hf←{(p q)←○⍺ ⍵÷180 ⋄ 2×r×¯1○(+/(2*⍨1○(p-q)÷2)×1(×/2○⊃¨p q))*÷2}
36.12 ¯86.67 hf 33.94 ¯118.40
