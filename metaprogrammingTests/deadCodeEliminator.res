Code was: 
for(i = 0; i < 10; i++){
	if(x = 5){
		print("here\n");
		if (y < 3)
			break;
		break;		
		x = i;
	}
	print(i, "\n");
}

function myTestFunc(){
	print("in test func\n");
}
				
function f(x, y, z){
	w = x*y + z;
	return 12;
	w = x*y + 6;
}
while (y = 5) {
	if (0) {
		for (i = 0; i = 3; i++)
			print("5\n");
	}
	while (nil) {
		x++;
	}
	for (i = 0; false; i++)
		x++;
}
while (true) {
	if (false)
		x++;
	else
		x--;
}

return 19;
print("after\n");

2.000000 WARNING: assignment in expression
21.000000 WARNING: assignment in expression


After elimination of dead code: 
for (i = 0.000000; i < 10.000000; i++)
{
if (x = 5.000000)
{
print("here\n");
if (y < 3.000000)
break;
break;
}
print(i, "\n");
}
function myTestFunc() {
print("in test func\n");
}
function f(x, y, z) {
w = x * y + z;
return 12.000000;
}
while (y = 5.000000) {
;
;
;
}
{
x--;
}
return 19.000000;
