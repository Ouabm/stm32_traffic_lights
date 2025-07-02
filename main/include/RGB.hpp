#ifndef RGB_HPP
#define RGB_HPP

#include <iostream>
#include <iomanip>

struct RGB {
    u_int8_t R;
    u_int8_t G;
    u_int8_t B;

    bool operator==(const RGB& a) const {
        return (R == a.R && G == a.G && B == a.B);
    }

    explicit RGB(u_int8_t _r, u_int8_t _g, u_int8_t _b): R(_r), G(_g), B(_b) {};
};

#ifndef NO_LOGGING
	/**
	 * Insertion operator for dll_frame objects.
	 * @param out output stream.
	 * @param b bid to be represented in the output stream.
	 * @return output stream with the value of the bid already inserted.
	 */
	std::ostream& operator<<(std::ostream& out, const RGB& colour) {
		// out << "{ RGB: ";
        // out << (unsigned int) colour.R << ", " << (unsigned int) colour.G << ", " << (unsigned int) colour.B;
        // out << " }";
        out << "0x" << std::setfill ('0') << std::setw(sizeof(u_int8_t)*2)  << std::hex << (unsigned int)colour.R ;
        out << std::setfill ('0') << std::setw(sizeof(u_int8_t)*2)  << std::hex << (unsigned int)colour.G;
        out << std::setfill ('0') << std::setw(sizeof(u_int8_t)*2)  << std::hex << (unsigned int)colour.B;
		
		return out;
	}
#endif
#endif // RGB_HPP



