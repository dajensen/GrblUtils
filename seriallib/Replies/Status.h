
class StatusReply : public GrblReply
{
    std::string status;
    double machine_coords[AxisNames::NUM_AXES];
    double workspace_coords[AxisNames::NUM_AXES];
    static double workspace_offsets[AxisNames::NUM_AXES];
    int planner_free;
    int rx_free;

    void status_element_to_doubles(double *doubles, std::string values) {
        std::vector<std::string> axis_values;
        split(values, ',', axis_values);
        for(int i = 0; i < std::min((int)axis_values.size(), (int)AxisNames::NUM_AXES); i++) {
            doubles[i] = std::stod(axis_values[i]);
        }
    }

    void subtract_double_arrays(double *dest, double *val1, double *val2) {
        for(int i = 0; i < AxisNames::NUM_AXES; i++){
            dest[i] = val1[i] - val2[i];
        }       
    }

    void add_double_arrays(double *dest, double *val1, double *val2) {
        for(int i = 0; i < AxisNames::NUM_AXES; i++){
            dest[i] = val1[i] + val2[i];
        }       
    }

    void status_element_to_intpair(int &i1, int &i2, std::string values) {
        std::vector<std::string> split_values;
        split(values, ',', split_values);
        if(split_values.size() > 0)
            i1 = std::stoi(split_values[0]);
        if(split_values.size() > 1)
            i2 = std::stoi(split_values[1]);
    }


public:
    StatusReply(std::string s) : GrblReply(s) {

        // An Example status message:
        // <Idle|WPos:0.000,0.000,10.000,-125.000,0.000|Bf:35,255|FS:0,0|WCO:0.000,0.000,-10.000,125.000,0.000>
        // Or this one
        // <Idle|WPos:0.000,0.000,10.000,-125.000,0.000|Bf:35,255|FS:0,0|Ov:100,100,100>
        // Or the simplest one
        // <Idle|WPos:0.000,0.000,10.000,-125.000,0.000|Bf:35,255|FS:0,0>

        // Status (Idle, Run, Hold, Jog, Alarm, Door, Check, Home, Sleep)
        // Current position wpos or mpos for each axis (may be machine position or work position depending on $10, and units are specified by $13)
        // Work Coordinate offset wco (Wco is the offsets between machine position and work position )
        // Buffer State bf (free blocks in planner, free bytes in rx buffer)
        // Line number ln (compare with the N value in $G - there's a difference between queueing and executing line) (may not be enabled)
        // F: current feed rate
        // FS: current feed rate, spindle speed
        // Ov: override values as a percent of programmed feed, rapids, and speed values

        std::vector<std::string> stringparts;
        split(trim(s, WHITESPACE + "<>"), '|', stringparts);
        if(stringparts.size() > 0)
            status = stringparts[0];       
        else
            status = "Unknown";

        bool have_machine_pos = false;
        for(int i = 1; i < stringparts.size(); i++) {
            std::vector<std::string> nameval;
            split(stringparts[i], ':', nameval);
            if(nameval.size() > 1){
                if(nameval[0] == "WPos"){
                    status_element_to_doubles(workspace_coords, nameval[1]);
                }
                if(nameval[0] == "MPos"){
                    status_element_to_doubles(machine_coords, nameval[1]);
                    have_machine_pos = true;
                }
                if(nameval[0] == "WCO"){
                    status_element_to_doubles(workspace_offsets, nameval[1]);
                }
                if(nameval[0] == "Bf"){
                    status_element_to_intpair(planner_free, rx_free, nameval[1]);
                }
            }
        }
        if(have_machine_pos)
            subtract_double_arrays(workspace_coords, machine_coords, workspace_offsets);
        else
            add_double_arrays(machine_coords, workspace_coords, workspace_offsets);
    }

    ~StatusReply() {}

    static bool Recognized(std::string raw) {return startswith(raw, "<");}
    static std::unique_ptr<GrblReply> CreateInstance(std::string raw) {
        GrblReply *baseptr = (GrblReply *) new StatusReply(raw);
        return std::unique_ptr<GrblReply>(baseptr);
    }

    std::string GetStatus() {return status;}
    double GetMachineCoordinates(AxisNames axis) {return machine_coords[axis];}
    double GetWorkspaceCoordinates(AxisNames axis) {return workspace_coords[axis];}
    int GetPlannerSlotsFree() {return planner_free;}
    int GetRxBytesFree() {return rx_free;}
};
