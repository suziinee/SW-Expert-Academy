T = int(input())
for t in range(T) :
    n = int(input())
    arr = [[0] * n for i in range(n)]
    x = 0
    y = -1
    i = 0

    dx = [0, 1, 0, -1]
    dy = [1, 0, -1, 0]

    for tmp in range(1, n**2+1) :
        # 처음 nx, ny
        nx = x + dx[i]
        ny = y + dy[i]
      
        if ny>=n :
        	i = 1
        if nx>=n :
            i = 2
        if ny<0 :
            i = 3
       	if nx<0 :
            i = 0
        
        while 0<=nx<n and 0<=ny<n :
            if i==0 and arr[nx][ny] != 0 :
                i = 1
                break
            if i==1 and arr[nx][ny] != 0 :
                i = 2
                break
            if i==2 and arr[nx][ny] != 0 :
                i = 3
                break
            if i==3 and arr[nx][ny] != 0 :
                i = 0
                break
            break
       
    	# 수정 후 nx, ny
        nx = x + dx[i]
        ny = y + dy[i]
        # 넣기
        arr[nx][ny] = tmp
        x = nx
        y = ny
        
    print(f"#{t+1}")
    for a in arr :
        print(*a)
		
    
    