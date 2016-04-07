samephore visited[n]={1,1,...,1};
samephore buffer[n]={1,1,...,1};

进程P_producer[1,2,...,m] //这m个进程中的每一个都必须独占资源
begin
if (visited[n]=={1,1,...,1})
{
P(buffer[n]);
visited[n]={0,0,...,0};
V(buffer[n]);
}
else ;
end

进程P_consumer[1,2,...,n] //这n个进程各用各的资源
begin
if (visited[1,2,...,n]==0)
{
P(buffer[1,2,...,n]);
visited[1,2,...,n]=1;
V(buffer[1,2,...,n]);
}
else ;
end

