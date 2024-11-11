function renderAST(json) {
    const data = JSON.parse(json);

    const width = 800;
    const height = 600;
    const margin = { top: 40, right: 20, bottom: 40, left: 20 };

    const svg = d3.select("body").append("svg")
        .attr("width", width)
        .attr("height", height);

    const root = d3.hierarchy(data, d => {
        if (d.type === "BinaryOp") {
            return [d.left, d.right];
        } else if (d.type === "UnaryOp") {
            return [d.operand];
        }
        return null;
    });

    const treeLayout = d3.tree().size([width - margin.left - margin.right, height - margin.top - margin.bottom]);
    treeLayout(root);

    const g = svg.append("g")
        .attr("transform", `translate(${margin.left},${margin.top})`);

    g.selectAll(".link")
        .data(root.links())
        .enter()
        .append("path")
        .attr("class", "link")
        .attr("fill", "none")
        .attr("stroke", "#ccc")
        .attr("stroke-width", 2)
        .attr("d", d3.linkHorizontal()
            .x(d => d.x)
            .y(d => d.y)
        );

    const node = g.selectAll(".node")
        .data(root.descendants())
        .enter()
        .append("g")
        .attr("transform", d => `translate(${d.x},${d.y})`)
        .attr("class", "node");

    node.append("rect")
        .attr("width", 80)
        .attr("height", 30)
        .attr("x", -40)
        .attr("y", -15)
        .attr("rx", 6)
        .attr("fill", d => d.data.type === "BinaryOp" ? "#FFCC33" : (d.data.type === "UnaryOp" ? "#FFA500" : "#66BB66"))
        .attr("stroke", "#000")
        .attr("stroke-width", 1);

    node.append("text")
        .attr("dy", 5)
        .attr("text-anchor", "middle")
        .attr("font-size", "12px")
        .attr("fill", "white")
        .text(d => {
            if (d.data.type === "Number") {
                return d.data.value;
            } else if (d.data.type === "BinaryOp" || d.data.type === "UnaryOp") {
                return d.data.op;
            }
            return d.data.type;
        });
}
