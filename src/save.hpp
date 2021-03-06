#ifndef SAVE_HPP_
#define SAVE_HPP_

#include <cassert>

#include <utils.hpp>
#include <parameters.hpp>

/**
 * @brief Save a vector
 *
 * Save a vector into a file, writing this vector on a single line using the given separator
 * and the given writing mode. Template method.
 * @param {const std::vector<T> &} v; the saved vector
 * @param {const std::string &} output_path; the output path (name of the file)
 * @param {const std::string &} separator; the used separator
 * @param {std::ofstream::openmode} mode; the mode: using 'std::ofstream::out' overrides the
 * output file while using 'std::ofstream::app' appends the vector to the bottom of the file.
 * Default is overriding.
 */
template <class T>
void save_vector(
    const std::vector<T> &v,
    const std::string &output_path,
    const std::string &separator,
	std::ofstream::openmode mode = std::ofstream::out)
{
    std::ofstream outfile;
	outfile.open(output_path,mode);
	for(unsigned int i=0; i<v.size(); ++i) {
		outfile << v[i];
		if(i<v.size()-1) {
            outfile << separator;
		}
	}
	outfile << std::endl;
	outfile.close();
}

/**
 * @brief Save a matrix
 *
 * Save a matrix into a file, writing subsequently each one of its line using the method
 * 'save_vector'. Template method.
 * @param {const std::vector<std::vector<T>> &} m; the saved matrix
 * @param {const std::string &} output_path; the output path (name of the file)
 * @param {const std::string &} separator; the used separator
 * @param {std::ofstream::openmode} mode; the mode: using 'std::ofstream::out' overrides the
 * output file while using 'std::ofstream::app' appends the vector to the bottom of the file.
 * Default is overriding.
 */
template <class T>
void save_matrix(
    const std::vector<std::vector<T>> &m,
    const std::string &output_path,
    const std::string &separator,
	std::ofstream::openmode mode = std::ofstream::out)
{
    for(auto &line : m) {
        save_vector(line,output_path,separator,mode);
    }
}

/**
 * @brief Initialize the backup file
 *
 * Overrides the name of the saved values at the given output path. This is the header used
 * for plotting.
 * @param {const std::vector<std::string> &} names; the names of the saved values
 * @param {const std::string &} output_path; the output path (name of the file)
 * @param {const std::string &} separator; the used separator
 */
void initialize_backup(
    const std::vector<std::string> &names,
    const std::string &output_path,
    const std::string &separator)
{
    save_vector(names,output_path,separator,std::ofstream::out);
}

/**
 * @brief Get the saved values names
 *
 * Get a vector containing the names of the saved values during each simulation.
 * @warning The values should be saved in the same ordering as in the 'simulate_episode'
 * method (edit 22/09/2017).
 * @return Return a vector containing each name in order of appearance
 */
std::vector<std::string> get_saved_values_names() {
    std::vector<std::string> v;
    v.emplace_back("score");
    v.emplace_back("computational_cost");
    v.emplace_back("nb_calls");
    return v;
}

void append_double(std::string &path, double d, std::string sep) {
    assert(!is_less_than(d,0.));
    if(is_equal_to(d,0.)) {
        path += "00";
    } else if(is_less_than(d,.1)) {
        path += "00";
        d = 100.*d;
    } else if (is_less_than(d,1.)) {
        path += "0";
        d = 100.*d;
    }
    path += std::to_string((int) d);
    path += sep;
}

/**
 * @brief Get the backup path
 *
 * Get a string with the path of the saved file wrt the parameters values
 * (see data/readme.txt).
 * @return Return backup path.
 */
std::string get_backup_path(const parameters &sp) {
    std::string sep = "_";
    std::string path = "data/";
    path += std::to_string(sp.POLICY_SELECTOR);
    path += sep;
    append_double(path,sp.TRACK_LEN,sep);
    append_double(path,sp.STDDEV,sep);
    append_double(path,sp.FAILURE_PROBABILITY,sep);
    path += std::to_string(sp.BUDGET);
    path += sep;
    path += std::to_string(sp.HORIZON);
    path += sep;
    append_double(path,sp.UCT_CST,sep);
    append_double(path,sp.DISCOUNT_FACTOR,sep);
    append_double(path,sp.EPSILON,sep);
    append_double(path,sp.MODEL_TRACK_LEN,sep);
    append_double(path,sp.MODEL_STDDEV,sep);
    append_double(path,sp.MODEL_FAILURE_PROBABILITY,".csv");
    return path;
}

#endif // SAVE_HPP_
