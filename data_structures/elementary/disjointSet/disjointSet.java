// This represents a 
class DSJ {
    static int[] parent;
    // Setting each of the nodes to be pointing at themselves
    public DSJ(){
        parent = new int[10001];
        for(int i = 0; i <= 10000; ++i)
            parent[i] = i;
    }
    public static int find(int x){
        if(parent[x] != x){return find(parent[x]);}
        return parent[x];
    }
    public static void union(int x, int y){
        // Unioning by setting 
        parent[find(x)] = find(y);
    }
}
