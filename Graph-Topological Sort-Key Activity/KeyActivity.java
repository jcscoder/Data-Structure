

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.LinkedList;
import java.util.Queue;

public class KeyActivity {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		StreamTokenizer st = new StreamTokenizer(
				new BufferedReader(new InputStreamReader(System.in)));
		st.nextToken();
		int nCheck = (int) st.nval;//The number of check points
		int time[][] = new int[nCheck][nCheck];//The lasting time of an activity between 2 check points
		int input[][] = new int[nCheck][nCheck];//The input order of each activity
		int inDegree[] = new int[nCheck];
		int outDegree[] = new int[nCheck];
		init(time, input, inDegree, outDegree);//Initialize arrays
		st.nextToken();
		int nActivity = (int) st.nval;//The number of activities
		for (int i = 0; i < nActivity; i ++) {
			st.nextToken();
			int x = (int) st.nval - 1;//One of the 2 check points of an activity
			st.nextToken();
			int y = (int) st.nval - 1;//Another check point of the activity
			st.nextToken();
			int lastingTime = (int) st.nval;//The lasting time of the activity
			time[x][y] = lastingTime;
			input[x][y] = i;//The i-th input
			inDegree[y] ++;
			outDegree[x] ++;//x->y, x out, y in
		}
		top(time, input, inDegree, outDegree);//find out the key activities
	}

	/* Initialize the graph and arrays. */
	private static void init(int[][] time, int[][] input, int[] inDegree, int[] outDegree) {
		// TODO Auto-generated method stub
		int nCheck = time.length;
		for (int i = 0; i < nCheck; i ++) {
			for (int j = 0; j < nCheck; j ++) 
				time[i][j] = input[i][j] = -1;
			inDegree[i] = outDegree[i] = 0;
		}
	}
	
	/* Top sort, find out the key activities. */
	private static void top(int[][] time, int[][] input, int[] inDegree, int[] outDegree) {
		// TODO Auto-generated method stub
		int nCheck = time.length;//The number of check points
		int count = 0;
		Queue <Integer> queue = new LinkedList<Integer>();
		int earliest[] = new int[nCheck];//The earliest starting time of each check points
		for (int v = 0; v < nCheck; v ++) {//v: Vertexes(check points) of the graph
			earliest[v] = 0;//Initialize
			if (inDegree[v] == 0) {
				queue.offer(v);
				count ++;
			}
		}
		while (! queue.isEmpty()) {
			int v = queue.poll();
			for (int w = 0; w < nCheck; w ++) 
				if (time[v][w] != -1) {//In the graph, v->w has edge
					/* If the earliest starting time of v + the time of activity between 
					 * v->w lager than the earliest starting time of w, 
					 * so w can not start so early*/
					if (earliest[v] + time[v][w] > earliest[w])
						earliest[w] = earliest[v] + time[v][w];
					if (--inDegree[w] == 0) {					
						queue.offer(w);							
						count ++;
					}
				}
		}//while
		if (count < nCheck) {
			System.out.println("0");
			return ;
		}
		//else
		int max = 0;
		for (int v = 0; v < nCheck; v ++) {
			if (outDegree[v] == 0) {
				queue.offer(v);
				if (earliest[v] > max)//Find the maximum earliest starting time of the
					max = earliest[v]; //check points with "outDegree" zero
			}
		}
		System.out.println(max);
		int latest[] = new int[nCheck];//The latest ending time of each check points
		for (int v = 0; v < nCheck; v ++)
			latest[v] = max;//Initialize
		while (!queue.isEmpty()) {
			int v = queue.poll();
			for (int w = 0; w < nCheck; w ++) {
				if (time[w][v] != -1) {//w->v has edge in the graph
					/* If the latest ending time of v - the time of activity between
					 * w->v smaller than the latest ending time of w,
					 * then w can not end so late*/
					if (latest[v] - time[w][v] < latest[w]) 
						latest[w] = latest[v] - time[w][v];
					/* If the latest ending time of v - the earliest starting time of
					 * w - the time of the activity between w->v greater than 0,
					 * then w->v is not key activity*/
					if (latest[v] - earliest[w] - time[w][v] > 0)
						time[w][v] = -1;//w->v is not key activity
					if (--outDegree[w] == 0)
						queue.offer(w);
				}
			}
		}//while
		for (int v = 0; v < nCheck; v ++) {
			count = 0;
			for (int w = 0; w < nCheck; w ++) 
				if (time[v][w] != -1)//v->w is key activity
					count ++;
			if (count == 0)
				continue;
			int arr[] = new int[count];
			count = 0;
			for (int w = 0; w < nCheck; w ++)
				if (time[v][w] != -1)
					arr[count ++] = w;
			sort(arr, input, v);
			for (int i = 0; i < count; i ++)
				System.out.println((v + 1) + "->" + (arr[i] + 1));
		}
	}

	/* Sorts. */
	private static void sort(int[] arr, int[][] input, int v) {
		// TODO Auto-generated method stub
		int si, d;
		int sedgewick[] = {41, 19, 5, 1, 0};
		int n = arr.length;
		for (si = 0; sedgewick[si] >= n; si ++)
			;
		for (d = sedgewick[si]; d > 0; d = sedgewick[++si]) {
			for (int p = d; p < n; p +=d) {
				int temp = arr[p];
				int i;
				for (i = p; i > 0 && input[v][arr[i - d]] < input[v][temp]; i -= d)
					arr[i] = arr[i - d];
				arr[i] = temp;
			}
		}
	}

}
