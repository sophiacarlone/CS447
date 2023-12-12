filename = input("Enter the name of the file you would like to open: ")

    num_vertices = calc_num_vertices(filename)

    source, terminal = calc_source_and_terminal(filename)

    graph1 = Graph(num_vertices)

    graph1.read_graph(filename)
