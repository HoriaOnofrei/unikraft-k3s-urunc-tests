#include <botan/hash.h>
#include <botan/hex.h>

#include <fstream>
#include <iostream>

#define CHUNKSIZE 4096

int main()
{
	// Initial variables
	const auto hash = Botan::HashFunction::create_or_throw("SHA-3");
	std::ifstream inputFile;
	std::ofstream outputFile;
	std::vector<uint8_t> buffer(CHUNKSIZE);

	// Open the input file
	std::cout << "Opening " << "input.in" << "..." << std::endl;
	inputFile.open("input.in");
	std::cout << "Opened " << "input.in" << std::endl;
	if (inputFile.rdstate() != 0)
	{
		std::cout <<"Input file could not open or is empty, exiting..." << std::endl;
		return 1;
	}
	std::cout << "Opening " << "output.out" << "..." << std::endl;

	// Open the output file
	outputFile.open("output.out");
	std::cout << "Opened " << "output.out" << std::endl;
	if (inputFile.rdstate() != 0)
	{
		std::cout <<"Output file could not open, exiting..." << std::endl;
		return 1;
        }

	// Begin the main loop: read parts of the input, and process it in chunks
	std::cout << "Starting the input reading and processing loop, state=" << inputFile.rdstate() << std::endl;
	while (!inputFile.eof())
	{
		// Read from the input file
		inputFile.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
		std::cout << "Read count=" << inputFile.gcount() << std::endl;

		// Update hash computations with read data
		hash->update(buffer.data(), inputFile.gcount());
	}
	std::cout << "Finished the loop, final state=" << inputFile.rdstate() << std::endl;

	// Write to the output file
	size_t hashLength = hash->output_length();
	outputFile.write(reinterpret_cast<const char*>(hash->final().data()), hashLength);
	std::cout << "Finished writing to output, count " << hashLength << std::endl;

	// Close files
	inputFile.close();
	outputFile.close();
	std::cout << "Closed files, exiting..." << std::endl;

	return 0;
}
