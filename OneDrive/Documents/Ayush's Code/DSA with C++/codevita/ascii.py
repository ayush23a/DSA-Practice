import sys

def solve():
    # 1. Read Input
    try:
        input_line = sys.stdin.read().strip()
        if not input_line:
            return
    except Exception:
        return

    specs = input_line.split()
    
    # List to store the 2D grid (list of strings) for each house
    houses_data = []
    max_total_height = 0

    # 2. Process each house specification
    for spec in specs:
        # Parse format: length<x>height<direction> e.g., 2x4H
        # Find the position of 'x'
        x_idx = spec.find('x')
        
        # The direction is the last character
        direction = spec[-1]
        
        # Extract length and height
        # length is from start to 'x'
        length_str = spec[:x_idx]
        # height is from 'x'+1 to the last character (direction)
        height_str = spec[x_idx+1:-1]
        
        width = int(length_str)
        wall_section_height = int(height_str)
        
        # --- Build the House ---
        
        house_lines = []
        
        # A. Build Roof
        # Roof height is half the width
        roof_height = width // 2
        
        # Generate Roof lines
        current_roof = []
        for i in range(roof_height):
            # Logic:
            # Row 0: (w/2 - 1) spaces, '/', 0 spaces, '\'
            # Row 1: (w/2 - 2) spaces, '/', 2 spaces, '\'
            outer_spaces = (width // 2) - 1 - i
            inner_spaces = 2 * i
            
            line = " " * outer_spaces + "/" + " " * inner_spaces + "\\" + " " * outer_spaces
            
            # Handle edge case if width is odd (though constraints imply even mostly)
            # If width is odd, the math above might need adjustment, 
            # but standard ascii houses usually assume even width for symmetry.
            # We adjust padding to strictly match width.
            while len(line) < width:
                line += " "
            
            current_roof.append(line)
            
        # B. Build Walls and Base
        # Number of wall rows (with @ and &) = input_height - 1 (for base)
        # Base row = 1
        
        current_walls = []
        
        # Determine wall characters based on direction (Mirroring)
        left_wall_char = '@'
        right_wall_char = '&'
        
        if direction in ['L', 'R']:
            # Mirror reflection: Swap characters
            left_wall_char = '&'
            right_wall_char = '@'
            
        # Generate Wall rows
        # The wall section is the rectangular part below roof. 
        # Total height given is 'wall_section_height'.
        # So we have (wall_section_height - 1) rows of walls + 1 row of base.
        
        for _ in range(wall_section_height - 1):
            if width > 1:
                line = left_wall_char + " " * (width - 2) + right_wall_char
            else:
                # Edge case for width=1, unlikely given constraints
                line = left_wall_char 
            current_walls.append(line)
            
        # Generate Base
        base_line = "#" * width
        current_walls.append(base_line)
        
        # C. Assemble House
        full_house = current_roof + current_walls
        
        # D. Handle Orientation 'D' (Down/Inverted)
        if direction == 'D':
            full_house = full_house[::-1] # Reverse the list
            
        houses_data.append(full_house)
        
        # Track maximum height for alignment later
        if len(full_house) > max_total_height:
            max_total_height = len(full_house)

    # 3. Alignment and Printing
    # We must print line by line.
    # Houses shorter than max_total_height need top-padding.
    
    final_output_lines = []
    
    for r in range(max_total_height):
        row_string = ""
        for house in houses_data:
            # Calculate how much padding this specific house needs
            padding_needed = max_total_height - len(house)
            
            # If the current row index 'r' is within the padding zone
            if r < padding_needed:
                # Print empty space equivalent to house width
                house_width = len(house[0]) # Grab width from the first real line
                row_string += " " * house_width
            else:
                # Calculate the actual index inside the house list
                house_row_idx = r - padding_needed
                row_string += house[house_row_idx]
            
            # No gap specified in prompt "appearing seamlessly side by side",
            # but typically standard console output implies directly adjacent.
            # If a space gap is needed, uncomment the line below:
            # row_string += " " 
            
        final_output_lines.append(row_string)

    # Print result
    for line in final_output_lines:
        print(line)

# Execute
if __name__ == "__main__":
    solve()