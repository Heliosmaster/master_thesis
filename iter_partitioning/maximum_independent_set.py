from __future__ import print_function
from __future__ import unicode_literals

from collections import defaultdict
import sys,copy

def bipartiteMatch(graph):
    '''Find maximum cardinality matching of a bipartite graph (U,V,E).
    The input format is a dictionary mapping members of U to a list
    of their neighbors in V.  The output is a triple (M,A,B) where M is a
    dictionary mapping members of V to their matches in U, A is the part
    of the maximum independent set in U, and B is the part of the MIS in V.
    The same object may occur in both U and V, and is treated as two
    distinct vertices if this happens.'''
    
    # initialize greedy matching (redundant, but faster than full search)
    matching = {}
    for u in graph:
        for v in graph[u]:
            if v not in matching:
                matching[v] = u
                break
    
    while 1:
        # structure residual graph into layers
        # pred[u] gives the neighbor in the previous layer for u in U
        # preds[v] gives a list of neighbors in the previous layer for v in V
        # unmatched gives a list of unmatched vertices in final layer of V,
        # and is also used as a flag value for pred[u] when u is in the first layer
        preds = {}
        unmatched = []
        pred = dict([(u,unmatched) for u in graph])
        for v in matching:
            del pred[matching[v]]
        layer = list(pred)
        
        # repeatedly extend layering structure by another pair of layers
        while layer and not unmatched:
            newLayer = {}
            for u in layer:
                for v in graph[u]:
                    if v not in preds:
                        newLayer.setdefault(v,[]).append(u)
            layer = []
            for v in newLayer:
                preds[v] = newLayer[v]
                if v in matching:
                    layer.append(matching[v])
                    pred[matching[v]] = v
                else:
                    unmatched.append(v)
        
        # did we finish layering without finding any alternating paths?
        if not unmatched:
            unlayered = {}
            for u in graph:
                for v in graph[u]:
                    if v not in preds:
                        unlayered[v] = None
            return (matching,list(pred),list(unlayered))

        # recursively search backward through layers to find alternating paths
        # recursion returns true if found path, false otherwise
        def recurse(v):
            if v in preds:
                L = preds[v]
                del preds[v]
                for u in L:
                    if u in pred:
                        pu = pred[u]
                        del pred[u]
                        if pu is unmatched or recurse(pu):
                            matching[v] = u
                            return 1
            return 0

        for v in unmatched: recurse(v)

def read_mtx_file_as_graph(filename):
    f = open(filename,'r')
    for line in f:
        if not line.startswith('%'):
            number_of_rows = int(line.split()[0])
            number_of_columns = int(line.split()[1])
            break
    graph = defaultdict(list)
    [graph[int(line.split()[0])].append(int(line.split()[1])) for line in f]
    f.close()
    return graph,number_of_rows,number_of_columns

def write_independent_set_to_file(filename,A,B,offset):
    f = open(filename, 'w')
    for row in A:
        f.write(str(row) + '\n')
    for column in B:
        f.write(str(offset+column) + '\n')
    f.close()

def print_independent_set(A,B,offset):
    for row in A:
        sys.stdout.write(str(row)+' ');
    for column in B:
        sys.stdout.write(str(offset+column)+ ' ')
    sys.stdout.write('\n')

def read_list_from_file(filename):
    f=open(filename,'r')
    l=[]
    [l.append(int(line.split()[0])) for line in f]
    return l

def get_subgraph(graph,list):
    offset = len(graph)
    graph2 = copy.deepcopy(graph)
    for i in graph:
        if not i in list:
            del graph2[i]
            continue
        else:
            for j in graph[i]:
                if not offset+j in list:
                    graph2[i].remove(j)
            if not graph2[i]:
                del graph2[i]
    return graph2

def subgraph(graph,list,m,n):
    helper = [0]*(m+n+1)
    for i in list:
        helper[i] = 1
    graph2 = copy.deepcopy(graph)
    for i in graph:
        if not helper[i]:
            del graph2[i]
            continue
        else:
            for j in graph[i]:
                if not helper[m+j]:
                    graph2[i].remove(j)
            if not graph2[i]:
                del graph2[i]
    return graph2

if __name__ == "__main__":
    #input_matrix = 'tbdmatlab'
    input_filename = sys.argv[1]
    list_filename = sys.argv[2]
    output_filename = input_filename + '.set'
    #print("Reading graph")
    graph,m,n = read_mtx_file_as_graph(input_filename)
    #print(graph)
    #print("Reading list")
    l = read_list_from_file(list_filename)
    #print(l)
    #print("Getting subgraph")
    graph2 = subgraph(graph,l,m,n)
    #print(graph3)
    #print("Computing independent set")
    M, A, B = bipartiteMatch(graph2)
    A.sort()
    B.sort()
    write_independent_set_to_file(output_filename,A,B,m)
    #print_independent_set(A,B,len(graph))
