samephore availablehere=1;
samephore availablethere=1;
samephore cars_on_bridge=1;
samephore quest=0;

进程P_bridge
begin
quest=1;
end

进程P_here
begin
P(cars_on_bridge);
if (quest==0)
;
else 
{
P(availablehere);
quest=0;
V(availablehere);
}
V(cars_on_bridge);
end

进程P_there
begin
P(cars_on_bridge);
if (quest==0)
;
else 
{
P(availablethere);
quest=0;
V(availablethere);
}
V(cars_on_bridge);
end

