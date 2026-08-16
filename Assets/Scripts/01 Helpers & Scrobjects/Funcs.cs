using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text.RegularExpressions;
using UnityEngine;

public static class Funcs
{
    /// <summary>
    /// Framerate independent alternative to lerp.
    /// </summary>
    /// <param name="a">Starting value.</param>
    /// <param name="b">Target value.</param>
    /// <param name="lambda">Decay rate???.</param>
    /// <param name="dt">Frame time.</param>
    /// <returns></returns>
    public static float Damp(float a, float b, float lambda, float dt)
    {
        return Mathf.Lerp(a, b, 1 - Mathf.Exp(-lambda * dt));
    }
    
    public static string ConvertCamelCase(string input)
    {
        // Insert spaces before capital letters
        string spaced = Regex.Replace(input, @"(\p{Ll})(\p{Lu})", "$1 $2");

        // Capitalize the first letter of the result
        return CultureInfo.CurrentCulture.TextInfo.ToTitleCase(spaced);
    }
    
    public static float Remap(float value, float inMin, float inMax, float outMin, float outMax) 
    {
        return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
    }

    private struct Cell
    {
        public Vector2Int pos;
        public int f, g, h;
        public Vector2Int parent;

        public Cell(Vector2Int pos, int f, int g, int h, Vector2Int parent)
        {
            this.pos = pos;
            this.f = f;
            this.g = g;
            this.h = h;
            this.parent = parent;
        }
    }
    
    public static List<Vector2Int> AStar4Dir(Vector2Int start, Vector2Int end, int rows, int columns, Predicate<Vector2Int> isValid)
    {
        Debug.Log($"Starting AStar. Pathing from {start} to {end}. Dimensions are ({columns},{rows})");
        var openList = new List<Cell>{ new(start, 0, 0, 0, start) };
        var closedList = new Cell[columns, rows];
        for (var i0 = 0; i0 < closedList.GetLength(0); i0++)
        for (var i1 = 0; i1 < closedList.GetLength(1); i1++)
        {
            closedList[i0, i1].f = Int32.MaxValue;
        }

        while (openList.Count > 0)
        {
            var currentCell = openList[0];
            openList.RemoveAt(0);
            
            Debug.Log($"=====\ncurrentCell is {currentCell.pos}");
            Debug.Log("Removing currentCell from openList");
            
            for (var i = -1; i <= 1; i++)
            {
                for (var j = -1; j <= 1; j++)
                {
                    // 4 directional, so ignore corners
                    if (i == -1 && j == -1 ||
                        i == 1 && j == 1 ||
                        i == -1 && j == 1 ||
                        i == 1 && j == -1)
                    {
                        continue;
                    }
                    
                    var x = currentCell.pos.x + i;
                    var y = currentCell.pos.y + j;
                    
                    Debug.Log($"Checking cell successor at ({x}, {y})");
                    
                    // out of bounds check
                    if (x < 0 || x > columns-1 || y < 0 || y > rows-1)
                    {
                        Debug.Log("Out of bounds");
                        continue;
                    }
                    
                    if (!isValid(new Vector2Int(x, y)))
                    {
                        Debug.Log("Not on module body");
                        continue;
                    }
                    
                    if (end.x == x && end.y == y)
                    {
                        closedList[currentCell.pos.x, currentCell.pos.y] = currentCell;
                        closedList[x, y] = new Cell(new Vector2Int(x, y), 0, 0, 0, currentCell.pos);
                        Debug.Log("Found the end!!!");
                        Debug.Log("Closed List:");
                        foreach (var cell in closedList)
                        {
                            if (cell.f == Int32.MaxValue) continue;
                            Debug.Log($"{cell.pos}, f: {cell.f}");
                        }
                        Debug.Log("Open List:");
                        foreach (var cell in openList)
                        {
                            if (cell.f == Int32.MaxValue) continue;
                            Debug.Log($"{cell.pos}, f: {cell.f}");
                        }
                        // stop search
                        var finalPath = new List<Vector2Int>();
                        finalPath.Add(end);
                        var parent = currentCell;
                        var loopCount = 0;
                        Debug.Log("Start: " + start);
                        Debug.Log("End: " + end);
                        Debug.Log(new Vector2Int(x, y));
                        foreach (var cell in closedList)
                        {
                            if (cell.f == Int32.MaxValue) continue;
                            Debug.Log($"Cell: {cell.pos}. Parent is {cell.parent}");
                        }
                        while (parent.pos != start)
                        {
                            loopCount++;
                            if (loopCount > 999)
                            {
                                return null;
                            }
                            
                            Debug.Log(parent.pos);
                            finalPath.Add(parent.pos);
                            parent = closedList[parent.parent.x, parent.parent.y];
                        }
                        finalPath.Add(parent.pos);
                        // finalPath.Reverse();
                        return finalPath;
                    }
                    
                    var g = currentCell.g + Mathf.Abs(x - currentCell.pos.x) + Mathf.Abs(y - currentCell.pos.y);
                    var h = Mathf.Abs(x - end.x) + Mathf.Abs(y - end.y);
                    var f = g + h;
                    
                    Debug.Log($"successor.f is {f}");

                    if (currentCell.pos.x == x && currentCell.pos.y == y)
                    {
                        Debug.Log("Overlapping currentCell");
                        continue;
                    }

                    var openListCheck = false;
                    foreach (var cell in openList)
                    {
                        if (cell.pos.x == x && cell.pos.y == y)
                        {
                            Debug.Log($"Cell exists on openList with f of {cell.f}");
                            if (cell.f <= f)
                            {
                                Debug.Log("Cell with lower f exists on openList");
                                openListCheck = true;
                                break;
                            }
                        }
                    }
                    if (openListCheck) continue;
                    
                    if (closedList[x, y].f < f)
                    {
                        Debug.Log("Cell with lower f exists on closedList");
                        // this spot already taken by a better path
                        continue;
                    }
                    
                    Debug.Log("Adding successor to openList");
                    openList.Add(new(new Vector2Int(x, y), f, g, h, currentCell.pos));
                    openList.Sort((a, b) => a.f < b.f ? -1 : 1);
                }
            }
            
            Debug.Log($"Adding currentCell {currentCell.pos} to closedList");
            Debug.Log($"closedList dimensions are {closedList.GetLength(0)} x {closedList.GetLength(1)}");
            closedList[currentCell.pos.x, currentCell.pos.y] = currentCell;
        }

        return null;
    }
    
    public static Vector2 GetClosestDirection(Vector2 vector)
    {
        // Handle a zero/null vector default case
        if (vector == Vector2.zero) return Vector2.up; 

        // Determine if the vector is mostly horizontal or vertical
        if (Math.Abs(vector.x) > Math.Abs(vector.y))
        {
            // Mostly horizontal: Check if pointing right or left
            return vector.x > 0 ? Vector2.right : Vector2.left;
        }
        else
        {
            // Mostly vertical: Check if pointing up or down
            return vector.y > 0 ? Vector2.up : Vector2.down;
        }
    }
}
